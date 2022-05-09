const { app, BrowserWindow, ipcMain, nativeTheme } = require('electron');
const { Worker } = require('worker_threads');
const path = require('path');

console.log("Import successful");

// Init async worker for addons executions in background
const worker = new Worker(path.resolve(__dirname, 'worker.js'));

const channels = {
  step: new MessageChannel(),
  reset: new MessageChannel(),
  observe: new MessageChannel(),
  shape: new MessageChannel()
};

// Send ports for each addon command to async worker
for (id in channels)
  worker.postMessage({port: channels[id].port2}, [channels[id].port2]);

// Running particular addon command in worker
const callAddon = (worker, cmd, ...args) => {

  let request = cmd + "(" + args.join(",") + ")";
  channels[cmd].port1.postMessage(request);

  return new Promise(resolve => {
    channels[cmd].port1.once('message', (msg) => {
      resolve(msg);
    })
  });
}

const createWindow = () => {
  const mainWindow = new BrowserWindow({
    width: 1440,
    height: 1024,
    darkTheme: true,
    backgroundColor: '#111',
    webPreferences: {
      nodeIntegrationInWorker: true,
      preload: path.join(__dirname, 'preload.js'),
      backgroundThrottling: false,
      nodeIntegration: true 
    }
  });

  // Darkmode by default
  nativeTheme.themeSource = 'dark';

  mainWindow.loadFile('frontend/index.html');

  console.log("Frontend loaded");

  // Handle addon APIs from IPC
  ipcMain.handle('world:step', async (event, ...args) => {
    return callAddon(worker, 'step', ...args);
  });
  ipcMain.handle('world:reset', async (event, ...args) => {
    return callAddon(worker, 'reset', ...args);
  });
  ipcMain.handle('world:observe', async (event, ...args) => {
    return callAddon(worker, 'observe', ...args);
  });
  ipcMain.handle('world:shape', async (event, ...args) => {
    return callAddon(worker, 'shape', ...args);
  });
}

app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) 
      createWindow();
  });
});

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') app.quit();
});