!include "MUI2.nsh"
!include "FileAssociation.nsh"

Name "KBE"

; set the name of the installer
OutFile "kbe-win32-0.3.1.exe"

;Default installation folder
InstallDir $PROGRAMFILES32\KBE

;Get installation folder from registry if available
InstallDirRegKey HKCU "Software\KBE" ""
;Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "sources\COPYING"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU"
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\KBE"
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "KBE"
  var StartMenuFolder
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
;Languages
 
	!insertmacro MUI_LANGUAGE "English"
	!insertmacro MUI_LANGUAGE "Russian"

;--------------------------------

;Installation types
	InstType "Full"
	InstType "Minimal"
	
;--------------------------------
# create an install section.
Section ;"Editor"
 

	SetOutPath "$INSTDIR\doc"
	File "sources\doc\changelog.html"
	File "sources\doc\license.html"
	File "sources\doc\ostis-logo.png"
	File "sources\doc\style.css"

	SetOutPath "$INSTDIR"
	File "sources\AUTHORS"
	File "sources\COPYING"
	File "sources\icudt53.dll"
	File "sources\icuin53.dll"
	File "sources\icuuc53.dll"
	File "sources\kbe.exe"
	File "sources\Qt5Core.dll"
	File "sources\Qt5Gui.dll"
	File "sources\Qt5Widgets.dll"
	File "sources\Qt5Xml.dll"


;Store installation folder
  WriteRegStr HKCU "Software\KBE" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    ;Create shortcuts
CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
CreateShortCut "$SMPROGRAMS\$StartMenuFolder\KBE.lnk" "$INSTDIR\kbe.exe"
CreateShortCut "$SMPROGRAMS\$StartMenuFolder\User Manual.lnk" "$INSTDIR\manual\User Guide.pdf"
CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

!insertmacro MUI_STARTMENU_WRITE_END

SectionEnd

Section "Uninstall"
Delete "$INSTDIR\Uninstall.exe"

	Delete "$INSTDIR\doc\changelog.html"
	Delete "$INSTDIR\doc\license.html"
	Delete "$INSTDIR\doc\ostis-logo.png"
	Delete "$INSTDIR\doc\style.css"

	RMDir "$INSTDIR\doc"
	Delete "$INSTDIR\AUTHORS"
	Delete "$INSTDIR\COPYING"
	Delete "$INSTDIR\icudt53.dll"
	Delete "$INSTDIR\icuin53.dll"
	Delete "$INSTDIR\icuuc53.dll"
	Delete "$INSTDIR\kbe.exe"
	Delete "$INSTDIR\Qt5Core.dll"
	Delete "$INSTDIR\Qt5Gui.dll"
	Delete "$INSTDIR\Qt5Widgets.dll"
	Delete "$INSTDIR\Qt5Xml.dll"

	RMDir "$INSTDIR"


	Delete "$INSTDIR\example\ru\space\mercury.gwf"
	Delete "$INSTDIR\example\ru\space\sun_planets.gwf"
	Delete "$INSTDIR\example\ru\space\sun_system.gwf"
	Delete "$INSTDIR\example\ru\space\venus.gwf"
	Delete "$INSTDIR\example\ru\space\_keynodes.gwf"

	RMDir "$INSTDIR\example\ru\space"

	RMDir "$INSTDIR\example\ru"

	RMDir "$INSTDIR\example"

 
  Delete "$INSTDIR\plugins\scg\scg.dll"
  RMDir "$INSTDIR\plugins\scg"

  Delete "$INSTDIR\plugins\scs\scs.dll"
  RMDir "$INSTDIR\plugins\scs"
  
  RMDir "$INSTDIR\plugins"
  
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\examples.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\KBE.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

  RMDir "$INSTDIR"
  DeleteRegKey /ifempty HKCU "Software\KBE"
  
  ${unregisterExtension} ".gwf" "GWF File"
  ${unregisterExtension} ".scs" "SCs File"
SectionEnd

Section "Examples" example
	SectionIn 1
	
	SetOutPath "$INSTDIR\example\ru\space"
	File "sources\example\ru\space\mercury.gwf"
	File "sources\example\ru\space\sun_planets.gwf"
	File "sources\example\ru\space\sun_system.gwf"
	File "sources\example\ru\space\venus.gwf"
	File "sources\example\ru\space\_keynodes.gwf"

	SetOutPath "$INSTDIR\example\ru"

	SetOutPath "$INSTDIR\example"

	
	CreateShortCut "$SMPROGRAMS\$StartMenuFolder\examples.lnk" "$INSTDIR\example"
SectionEnd

SectionGroup "Plugins" plugins

	Section "SCg" scg
		SectionIn 1 2
		SetOutPath "$INSTDIR\plugins\scg"
		File "sources\plugins\scg.dll"
		
		${registerExtension} "$INSTDIR\kbe.exe" ".gwf" "GWF File"
	SectionEnd

	Section "SCs" scs
		SectionIn 1
		SetOutPath "$INSTDIR\plugins\scs"
		File "sources\plugins\scs.dll"
		
		${registerExtension} "$INSTDIR\kbe.exe" ".scs" "SCs File"
	SectionEnd
	
SectionGroupEnd

Function .onInit
	!insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

LangString DESC_Section1 ${LANG_ENGLISH} "Contains some samples written in SCg"
LangString DESC_Section1 ${LANG_RUSSIAN} "Содержит несколько примеров, записанных на SCg"
LangString DESC_Section2 ${LANG_ENGLISH} "Standard editor's components"
LangString DESC_Section2 ${LANG_RUSSIAN} "Стандартные компоненты"
LangString DESC_Section3 ${LANG_ENGLISH} "Component for SCg-text edit"
LangString DESC_Section3 ${LANG_RUSSIAN} "Компонент редактирования SCg-текстов"
LangString DESC_Section4 ${LANG_ENGLISH} "Component for SCs-text edit"
LangString DESC_Section4 ${LANG_RUSSIAN} "Компонент редактирования SCs-текстов"


!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${example} $(DESC_Section1)
  !insertmacro MUI_DESCRIPTION_TEXT ${plugins} $(DESC_Section2)
  !insertmacro MUI_DESCRIPTION_TEXT ${scg} $(DESC_Section3)
  !insertmacro MUI_DESCRIPTION_TEXT ${scs} $(DESC_Section4)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

