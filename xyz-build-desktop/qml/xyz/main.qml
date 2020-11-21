import Qt 4.7
import QtMultimediaKit 1.1

Rectangle {
    id:cameraui
    width: 1280
    height: 720
    color: "black"
    state: "PhotoCapture"
    PhotoPreview    {
        id:photoPreview
        anchors.fill : parent
                 onClosed: cameraUI.state = "PhotoCapture"
                 focus: visible

                 Keys.onPressed : {
                     //return to capture mode if the shutter button is touched
                     if (event.key == Qt.Key_CameraFocus) {
                         cameraUI.state = "PhotoCapture"
                         event.accepted = true;
                     }
                 }
    }

    Camera  {
        id:camera1
        x:0
        y:0
        width: 1280
        height: 720
        focus: visible
        flashMode: Camera.FlashOff
        whiteBalanceMode: Camera.WhiteBalanceAuto
        onImageCaptured: {
            photoPreview.source = preview
            stillControls.previewAvailable = true
            cameraUI.state = "PhotoPreview"
        }

    }
    states: [
        State {
            name: "PhotoCapture"
            StateChangeScript   {
                script:  {
                    camera1.visible=true
                    camera1.focus = true
                    photoPreview.visible = false
                }
            }
        },
        State {
            name: "PhotoPreview"
            StateChangeScript   {
                script: {
                    camera1.visible=false
                    photoPreview.visible = true
                    photoPreview.focus = true
                }
            }
        }
    ]


}
