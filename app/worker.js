const { step, reset, observe, shape } = require("./addon/build/Release/addon.node");
const { parentPort } = require('worker_threads');

console.log("addon imported");

reset();

parentPort.on('message', async (value) => {
    const { port } = value;

    port.on('message', (data) => {
        port.postMessage(eval(data));
    });
});