import React, { useRef, useState, useEffect } from "react";
import "./Canvas.scss";


const Canvas = () => {
    const canvasRef = useRef(null);

    const [canvasTag, setCanvasTag] = useState([]);

    useEffect(() => {
        const canvas = canvasRef.current;
        //canvas.width = window.innerHeight * 0.5;
        //canvas.height = window.innerHeight;

        //setCanvasTag(canvas)
    }, []);

    console.log("canvasTag :", canvasTag)

    return (
        <div className="canvas_wrap">
            {/*useRef*/}
            <canvas ref={canvasRef}></canvas>
        </div>
    );
};

export default Canvas;