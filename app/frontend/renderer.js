let state, shapes = {};

let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d", { alpha: false });

class Camera
{
    constructor(pointOfView, size, sizeOfView, offset=1)
    {
        this.pov = pointOfView;
        this.sov = sizeOfView;
        this.size = size;

        this.factor = Math.min(this.size.x / this.sov.x, this.size.y / this.sov.y) * (1 - offset);
    }

    tr(point)
    {
        let res = {};
        for (let axis in point)
            res[axis] = (point[axis] - this.pov[axis]) * this.factor + this.size[axis] / 2;

        return res;
    }

    rs(point)
    {
        return {x: point.x * this.factor, y: point.y * this.factor};
    }
};

let W, H, camera;
const canvasFit = () => {
    let rect = canvas.parentNode.getBoundingClientRect();
    canvas.width = rect.width;
    canvas.height = rect.height;
    W = canvas.width;
    H = canvas.height;

    camera = new Camera({x: 0, y: 0}, {x: W, y: H}, {x: 2.1, y: 1.5}, offset=0.03);
}

canvasFit();
window.onresize = canvasFit;

let iterTime = 1 / 60, prevTimeMeasure = 0;
const render = () => {
    // Fill background
    ctx.fillStyle = "#2E8F2C";
    ctx.fillRect(0, 0, W, H);

    // Fill the ROI
    let min = camera.tr({x: -1.1, y: -0.8});
    let max = camera.tr({x:  1.1, y:  0.8});
    let size = {w: max.x - min.x, h: max.y - min.y};

    // Draw all the objects
    ctx.lineWidth = 2;

    for (let key in state.objects)
    {
        // Draw object
        let shape = {...shapes[key]};
        let translation = camera.tr({...state.objects[key].position});
        let angle = state.objects[key].angle;

        let alpha = 'ff';
        if (state.objects[key].ghost)
            alpha = '20';

        ctx.fillStyle = '#0077aa' + alpha;
        ctx.strokeStyle = '#000000' + alpha;
        ctx.save();
        ctx.translate(translation.x, translation.y);
        ctx.rotate(angle);

        for (let part in shape)
        {
            let convexShape = {...shape[part]};
            for (let i in convexShape)
            {
                const point = {...convexShape[i]};
                convexShape[i] = {...camera.rs(point)};
            }
            
            ctx.beginPath();
            ctx.moveTo(convexShape[0].x, convexShape[0].y);

            for (let index in convexShape)
                ctx.lineTo(convexShape[index].x, convexShape[index].y);
            
            ctx.closePath();
            ctx.fill();
            ctx.stroke();
        }

        ctx.restore();

        // Draw AABB for each convex shape
        ctx.strokeStyle = '#602020' + alpha;
        for (let i in state.objects[key].shape)
        {
            let aabb = state.objects[key].shape[i];

            let min = camera.tr(aabb.min);
            let max = camera.tr(aabb.max);

            ctx.strokeRect(min.x, min.y, max.x - min.x, max.y - min.y);
        }

        // Draw AABB
        ctx.strokeStyle = '#905050' + alpha;
        let aabb = state.objects[key].aabb;

        let min = camera.tr(aabb.min);
        let max = camera.tr(aabb.max);

        ctx.strokeRect(min.x, min.y, max.x - min.x, max.y - min.y);

        // Draw center of mass for each shape
        ctx.strokeStyle = '#0000ff' + alpha;
        for (let i in state.objects[key].shape)
        {
            let centerOfMass = camera.tr(state.objects[key].COM);

            ctx.strokeRect(centerOfMass.x - 1, centerOfMass.y - 1, 2, 2);
        }
    }

    // Syncronize the simulation with real world
    let stepNumber = Math.round(iterTime * 0.001 / state.dt);
    // Addon calls
    world.step(1).then(() => {
        world.observe().then((result) => {
            state = result;

            iterTime = performance.now() - prevTimeMeasure;
            prevTimeMeasure = performance.now();

            requestAnimationFrame(render);
        });
    });
}

world.observe().then((result) => {
    state = result;
    
    // Nice hack that allow to use await
    (async () => {
        for (id in state.objects)
            shapes[id] = await world.shape(id);
        
        prevTimeMeasure = performance.now();
        render();
    })();
});