#Persistent
#NoEnv
SetBatchLines, -1
port := "\\.\COM4"  ; Ensure this is correct
file := FileOpen(port, "r")
if (!file) {
    MsgBox, Could not open COM4! Make sure it's not in use by another program.
    ExitApp
}
file.Seek(0)  ; Start at the beginning
Loop {
    line := file.ReadLine()
    if (line) {
        if (RegExMatch(line, "VOLUME:(\d+)", match)) {
            newVolume := match1
            SoundSet, newVolume, Master  ; Instantly set volume
            ToolTip, Volume: %newVolume%  ; Quick visual feedback (remove if unwanted)
        }
        else if (RegExMatch(line, "BRIGHTNESS:(\d+)", match)) {
            newBrightness := match1
            ChangeBrightness(newBrightness)
            ToolTip, Brightness: %newBrightness%  ; Quick visual feedback (remove if unwanted)
        }
    }
    Sleep, 5  ; Ultra-low delay, ensures stability
}

; Function to change screen brightness
ChangeBrightness(brightness) {
    ; Use the built-in Windows WMI interface to adjust brightness
    for device in ComObjGet("winmgmts:\\.\root\WMI").ExecQuery("SELECT * FROM WmiMonitorBrightnessMethods")
    {
        device.WmiSetBrightness(1, brightness)
        break  ; Only change the primary monitor
    }
    return
}
