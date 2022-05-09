// All of the Node.js APIs are available in the preload process.
// It has the same sandbox as a Chrome extension.
window.addEventListener('DOMContentLoaded', () => {
  const replaceText = (selector, text) => {
    const element = document.getElementById(selector);
    if (element) element.innerText = text;
  };

  for (const dependency of ['chrome', 'node', 'electron']) {
    replaceText(`${dependency}-version`, process.versions[dependency]);
  }
});

const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('world', {
  step: (...args) => ipcRenderer.invoke('world:step', ...args),
  observe: (...args) => ipcRenderer.invoke('world:observe', ...args),
  reset: (...args) => ipcRenderer.invoke('world:reset', ...args),
  shape: (...args) => ipcRenderer.invoke('world:shape', ...args)
});