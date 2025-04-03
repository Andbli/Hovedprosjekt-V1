#Persistent
#NoEnv
SetBatchLines, -1
Process, Priority, , BelowNormal  ; Lower priority to avoid interference with games

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
        }
    }
    Sleep, 5  ; Ultra-low delay, ensures stability
}
