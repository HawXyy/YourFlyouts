[Variables]
H=(#Height#*#scale#)
VolumeW=(80*#Scale#)
MediaW=(500*#Scale#)
LocksW=(#H#)
P=(20*#Scale#)

SliderM=(#P#+8*#scale#)
SliderW=(#H#-#P#*2-(30+8*2)*#Scale#)

[Sec.BottomButton:S]
X=(#P#*2)R
Y=r
W=(20*#scale#)
H=(20*#scale#)
Grayscale=1
ImageTint=#FontColor#
DynamicVariables=1
Group=Music | Standard
Container=MediaC

; ---------------------------------------------------------------------------- ;
;                                   Function                                   ;
; ---------------------------------------------------------------------------- ;


[mVolume]
Measure=Plugin
Plugin=Win7AudioPlugin
DynamicVariables=1
OnChangeAction=[!UpdateMeterGroup Dynamic][!Redraw]
UpdateDivider=1

[FrostedGlass]
Measure=Plugin
Plugin=FrostedGlass
Blur=Acrylic
Border=None
Corner=Round

[SliderPercent]
Measure=Calc
Formula=(100-(#SliderX#-(#SliderM#))*100/(((#SliderM#)+#SliderW#)-(#SliderM#)))
OnUpdateAction=[!CommandMeasure "mVolume" "SetVolume [#CURRENTSECTION#]"][!UpdateMeasure mVolume]
DynamicVariables=1
Disabled=1
Group=NUOL

[VolumeMouse]
Measure=Plugin
Plugin=Mouse
LeftMouseDragAction=[!SetVariable SliderX "(Clamp(($MouseY$),(#SliderM#),((#SliderM#)+#SliderW#)))"][!UpdateMeasure SliderPercent]
; actions to be executed when the mouse drags. The first bang gets the mouse value and make sure it's in the slider. The bangs after that updates the required measures and the slider.
LeftMouseUpAction=[!SetVariable SliderX "(Clamp(($MouseY$),(#SliderM#),((#SliderM#)+#SliderW#)))"][!UpdateMeasure SliderPercent][!CommandMeasure VolumeMouse "Stop"]
; actions to be executed after the mouse click is lifted. The first bang stops the measure to retrieve information from mouse dragging.
RelativeToSkin=1
RequireDragging=1
DynamicVariables=1


; --------------------------------- VolumeBar -------------------------------- ;

[VolumeB]
Meter=Shape
X=1
Y=1
Shape=Rectangle 0,0,#VolumeW#,#H#,#R# | StrokeWidth #Stroke# | Fill Color #PrimaryColor#,#PrimaryOpacity#
Group=Standard
MouseScrollUpAction=[!CommandMeasure "mVolume" "ChangeVolume 2"][!UpdateMeasure mVolume]
MouseScrollDownAction=[!CommandMeasure "mVolume" "ChangeVolume -2"][!UpdateMeasure mVolume]
[VolumeC]
Meter=Shape
X=r
Y=r
Shape=Rectangle 0,0,#VolumeW#,#H#,#R# | StrokeWidth 0
Group=Standard

[VolumeBar]
Meter=Shape
X=(#VolumeW#/2)
Y=(#SliderM#)
Shape=Line 0,#SliderW#,0,0 | StrokeWidth (3*#scale#) | Fill Color 0,0,0,1 | Stroke Color #FontColor#,50 | StrokeStartCap #Cap# | StrokeEndCap #Cap#
Shape2=Line 0,#SliderW#,0,(#SliderW#*(1-[mVolume:]/100)) | StrokeWidth (3*#Scale#) | Fill Color 0,0,0,1 | Stroke Color #AccentColor# | StrokeStartCap #Cap# | StrokeEndCap #Cap#
Shape3=Ellipse 0,(#SliderW#*(1-[mVolume:]/100)),(8*#scale#) | StrokeWidth 0 | Fill Color #FontColor#
LeftMouseDownAction=[!CommandMeasure VolumeMouse "Start"]
DynamicVariables=1
Group=Dynamic | Standard
Container=VolumeC

[VolumeString]
Meter=String
MeterStyle=String:S
X=(#VolumeW#/2)
Y=(#H#-#P#)
StringAlign=CenterBottom
FontSize=(10*#scale#)
Text=[mVolume:]
FontColor=#FontColor2#
DynamicVariables=1
Group=Dynamic | Standard
Container=VolumeC

; --------------------------------- Media -------------------------------- ;

[MediaB]
Meter=Shape
X=1
Y=r
Shape=Rectangle 0,0,(#MediaW#+#VolumeW#),#H#,#R# | StrokeWidth #Stroke# | Fill Color #PrimaryColor#,#PrimaryOpacity#
Shape2=Rectangle 0,0,#VolumeW#,#H#,#R# | StrokeWidth #Stroke#
Shape3=Combine Shape | XOR Shape2
Shape4=Line #VolumeW#,(#P#),#VolumeW#,(#P#+(#H#-#P#*2)*#TweenNode1#) | StrokeStartCap Round | StrokeEndCap ROund | StrokeWidth (1*#Scale#) | Stroke Color #FontColor#,50
DynamicVariables=1
Group=Music | Standard | Animated
[MediaC]
Meter=Shape
X=(#VolumeW#)
Y=r
DynamicVariables=1
Shape=Rectangle 0,0,(#MediaW#*#TweenNode1#),#H#,#R# | StrokeWidth 0 | Fill Color 255,255,255,(255*#TweenNode1#)
Group=Music | Standard | Animated

[MediaImage]
Meter=Image
X=(#MediaW#-#H#*1.5+#P#)
Y=0
W=(#H#*1.5)
H=(#H#)
PreserveAspectRatio=2
MaskImageName=#@#Images\FadeMask.png
ImageName=[#PlayerType#Cover]
DynamicVariables=1
Group=Music | Standard | MediaImage
Container=MediaC

[MediaPlayerImage]
Meter=Image
X=(8*#Scale#+#P#)
Y=(#P#+8*#Scale#)
W=(48*#Scale#)
H=(48*#Scale#)
PreserveAspectRatio=2
ImageName=#@#Icons\Players\[#PlayerType#Player].png
DynamicVariables=1
Group=Music | Standard
Container=MediaC

[MediaTrack]
Meter=String
MeterStyle=String:S
X=#P#R
Y=(#P#)
W=(#MediaW#-#P#*3-64*#Scale#)
FontSize=(18*#scale#)
ClipString=1
FontWeight=650
Text=[#PlayerType#Track]
DynamicVariables=1
Group=Music | Standard
Container=MediaC
[MediaArtist]
Meter=String
MeterStyle=String:S
X=r
Y=R
W=(#MediaW#-#P#*3-64*#Scale#)
FontSize=(12*#scale#)
ClipString=1
Text=[#PlayerType#Artist]
DynamicVariables=1
Group=Music | Standard
Container=MediaC

; ---------------------------------- Buttons --------------------------------- ;

[MediaShuffle]
Meter=Image
X=((#MediaW#)/2-(20*5*#scale#+#P#*2*4)/2)
Y=(#H#-#P#*4)
ImageName=#@#Icons\FluentShuffle.png
MeterStyle=Sec.BottomButton:S
[Shuffle0]
ImageAlpha=150
LeftMouseUpAction=[!SetOption MediaShuffle MeterStyle "Sec.BottomButton:S | Shuffle1"][!UpdateMeter MediaShuffle][!Redraw][!CommandMeasure state#NowPlayingMedia# "Shuffle"]
[Shuffle1]
ImageAlpha=255
LeftMouseUpAction=[!SetOption MediaShuffle MeterStyle "Sec.BottomButton:S | Shuffle0"][!UpdateMeter MediaShuffle][!Redraw][!CommandMeasure state#NowPlayingMedia# "Shuffle"]


[MediaPrev]
Meter=Image
ImageName=#@#Icons\FluentPrevious.png
LeftMouseUpAction=[!CommandMeasure state#NowPlayingMedia# "Previous"]
MeterStyle=Sec.BottomButton:S

[MediaPlayPause]
Meter=Image
MeterStyle=Sec.BottomButton:S
[Play]
ImageName=#@#Icons\FluentPlay.png
LeftMouseUpAction=[!SetOption MediaPlayPause MeterStyle "Sec.BottomButton:S | Pause"][!UpdateMeter MediaPlayPause][!Redraw][!CommandMeasure state#NowPlayingMedia# "PlayPause"]
[Pause]
ImageName=#@#Icons\FluentPause.png
LeftMouseUpAction=[!SetOption MediaPlayPause MeterStyle "Sec.BottomButton:S | Play"][!UpdateMeter MediaPlayPause][!Redraw][!CommandMeasure state#NowPlayingMedia# "PlayPause"]

[MediaNext]
Meter=Image
ImageName=#@#Icons\FluentNext.png
LeftMouseUpAction=[!CommandMeasure state#NowPlayingMedia# "Next"]
MeterStyle=Sec.BottomButton:S

[MediaRepeat]
Meter=Image
MeterStyle=Sec.BottomButton:S
LeftMouseUpAction=[!CommandMeasure state#NowPlayingMedia# "Repeat"]
[Repeat0]
ImageAlpha=150
ImageName=#@#Icons\FluentRepeat.png
[Repeat1]
ImageName=#@#Icons\FluentRepeat.png
[Repeat2]
ImageName=#@#Icons\FluentRepeat2.png

[MediaHeart]
Meter=String

; ------------------------------------ Bar ----------------------------------- ;

[MediaCurrent]
Meter=String
MeterStyle=String:S
X=(35*#Scale#+#P#)
Y=(#H#-#P#*1.5)
FontWeight=600
FontColor=#FontColor2#
DynamicVariables=1
UpdateDivider=1
StringAlign=RightCenter
MeasureName=#PlayerType#CurrentPosition
Group=Music | Standard
Container=MediaC

[ProgBar]
Meter=Shape
X=(#P#)r
Y=r
Shape=Line 0,0,(#MediaW#-#P#*4-70*#Scale#),0 | StrokeWidth (2*#Scale#) | Fill Color 0,0,0,1 | Stroke Color #FontColor#,50 | StrokeStartCap #Cap# | StrokeEndCap #Cap#
Shape2=Line 0,0,((#MediaW#-#P#*4-70*#Scale#)*[#PlayerType#Progress]/100),0 | StrokeWidth (2*#Scale#) | Fill Color 0,0,0,1 | Stroke Color #AccentColor# | StrokeStartCap #Cap# | StrokeEndCap #Cap#
Shape3=Ellipse ((#MediaW#-#P#*4-70*#Scale#)*[#PlayerType#Progress]/100),0,(8*#scale#) | StrokeWidth 0 | Fill Color #FontColor#
LeftMouseUpAction=[!SetOption PosCalc Formula "($MouseX$/(#MediaW#-#P#*4-70*#Scale#)*100)"][!UpdateMeasure PosCalc]
DynamicVariables=1
UpdateDivider=1
Group=Music | Standard
Container=MediaC
[PosCalc]
Measure=calc
OnUpdateAction=[!CommandMeasure state#NowPlayingMedia# "SetPosition [PosCalc]"][!UpdateMeasure #PlayerType#Progress]
Disabled=1
DynamicVariables=1
UpdateDivider=-1
Group=NUOL

[MediaLength]
Meter=String
MeterStyle=String:S
X=(#MediaW#-#P#-35*#Scale#)
Y=r
FontColor=#FontColor2#
FontWeight=600
DynamicVariables=1
StringAlign=LeftCenter
MeasureName=#PlayerType#Length
Group=Music | Standard
Container=MediaC

; ---------------------------------------------------------------------------- ;
;                                    Special                                   ;
; ---------------------------------------------------------------------------- ;

; ----------------------------------- Caps ----------------------------------- ;

[LocksB]
Meter=Shape
X=1
Y=1
Shape=Rectangle 0,0,#LocksW#,#H#,#R# | StrokeWidth #Stroke# | Fill Color #PrimaryColor#,#PrimaryOpacity# | Stroke Color #SecondaryColor#,#SecondaryOpacity#
Group=Locks | Special
Hidden=1
[LocksC]
Meter=Shape
X=r
Y=r
Shape=Rectangle 0,0,#LocksW#,#H#,#R# | StrokeWidth 0
Group=Locks | Special
Hidden=1



[LocksIcon]
Meter=String
MeterStyle=String:S
X=(#Locksw#/2)
Y=(#Locksw#/2)
Text=[\xe835]
FontFace=Material Icons Round
StringAlign=CenterCenter
FontSize=(32*#scale#)
Group=Locks | Special
InlineSetting=Shadow | 0 | 0 | 10 | 0,0,0,150
Container=LocksC
Hidden=1
[LocksText]
Meter=String
MeterStyle=String:S
X=r
Y=(#P#*2)r
W=(#LocksW#)
StringAlign=Center
ClipString=2
FontSize=(8*#scale#)
Fontcolor=#FontColor2#
Group=Locks | Special
Container=LocksC
Hidden=1