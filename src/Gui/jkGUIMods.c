#include "jkGUIMods.h"

#include "General/stdBitmap.h"
#include "General/stdFont.h"
#include "Engine/rdMaterial.h" // TODO move stdVBuffer
#include "stdPlatform.h"
#include "jk.h"
#include "Gui/jkGUIRend.h"
#include "Gui/jkGUI.h"
#include "World/jkPlayer.h"
#include "Main/jkStrings.h"
#include "General/stdFnames.h"
#include "General/Darray.h"
#include "Gui/jkGUITitle.h"
#include "Gui/jkGUISingleplayer.h"
#include "Gui/jkGUIMultiplayer.h"
#include "Gui/jkGUIDialog.h"
#include "Gui/jkGUIPlayer.h"
#include "Gui/jkGUISetup.h"
#include "Gui/jkGUIMods.h"
#include "Win95/stdComm.h"
#include "Win95/stdGdi.h"
#include "Win95/Windows.h"
#include "Main/Main.h"
#include "Main/jkMain.h"
#include "Main/jkRes.h"
#include "General/stdString.h"
#include "General/util.h"
#include "General/stdFnames.h"
#include "General/stdFileUtil.h"
#include "stdPlatform.h"
#include "Main/InstallHelper.h"

#if defined(LINUX)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#endif

typedef struct jkGuiModsElement_t
{
    const char* paPath;
} jkGuiModsElement_t;

enum jkGuiModsButton_t
{
    JKGUIMODS_BTN_LISTCLICK = 1,
    JKGUIMODS_BTN_OPENRESOURCEFOLDER = 10,
};

static uint32_t jkGuiMods_listboxIdk[2] = {0xd, 0xe};

static jkGuiElement jkGuiMods_aElements[9] = {
    {ELEMENT_TEXT, 0, 5, L"Expansions & Mods", 3, {0, 30, 640, 60}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_LISTBOX, JKGUIMODS_BTN_LISTCLICK, 2, 0, 0, {80, 135, 480, 240}, 1, 0, 0, 0, 0, jkGuiMods_listboxIdk, {0}, 0},
    
    {ELEMENT_TEXT, 0, 2, L"This menu is slightly functional.", 3, {160, 100, 320, 30}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, JKGUIMODS_BTN_OPENRESOURCEFOLDER, 2, L"Open Resource Folder", 3, {160, 380, 320, 40}, 1, 0, 0, 0, 0, 0, {0}, 0},

    {ELEMENT_TEXT,  0,  0,  NULL,  3, {560, 440, 70, 15},  1,  0,  0,  0,  0,  0, {0},  0},
    {ELEMENT_TEXT,  0,  0,  NULL,  3, {560, 455, 70, 15},  1,  0,  0,  0,  0,  0, {0},  0},

    {ELEMENT_TEXTBUTTON, 1, 2, "GUI_OK", 3, {340, 420, 140, 40}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_TEXTBUTTON, -1, 2, "GUI_CANCEL", 3, {150, 420, 180, 40}, 1, 0, 0, 0, 0, 0, {0}, 0},
    {ELEMENT_END, 0, 0, 0, 0, {0}, 0, 0, 0, 0, 0, 0, {0}, 0}
};

static jkGuiMenu jkGuiMods_menu = {jkGuiMods_aElements, 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xF, 0, 0, jkGui_stdBitmaps, jkGui_stdFonts, 0, 0, "thermloop01.wav", "thrmlpu2.wav", 0, 0, 0, 0, 0, 0};

static int jkGuiMods_bInitted;

#if defined(MACOS)
int jkGuiMods_OpenURL(const char* url)
{
    return SDL_OpenURL(url);
}
#elif defined(LINUX)
// Lifted from SDL2
int jkGuiMods_OpenURL(const char *url)
{
    /* child process */
    const pid_t pid1 = fork();
    if (pid1 == 0) 
    { 
        pid_t pid2;
        /* Clear LD_PRELOAD so Chrome opens correctly when this application is launched by Steam */
        unsetenv("LD_PRELOAD");

        /* Notice this is vfork and not fork! */
        pid2 = vfork();
        if (pid2 == 0) 
        {  /* Grandchild process will try to launch the url */
            execlp("xdg-open", "xdg-open", url, NULL);
            _exit(EXIT_FAILURE);
        } 
        else if (pid2 < 0) 
        {   /* There was an error forking */
            _exit(EXIT_FAILURE);
        } 
        else 
        {
            /* Child process doesn't wait for possibly-blocking grandchild. */
            _exit(EXIT_SUCCESS);
        }
    } 
    else if (pid1 < 0) 
    {
        return 1;
    } 
    else 
    {
        int status;
        if (waitpid(pid1, &status, 0) == pid1) 
        {
            if (WIFEXITED(status)) 
            {
                 if (WEXITSTATUS(status) == 0) 
                 {
                     return 0;  /* success! */
                 }
             }
        }
    }
    return 0;
}
#else
int jkGuiMods_OpenURL(const char* url)
{
    return SDL_OpenURL(url);
}
#endif

void jkGuiMods_Startup()
{
    if ( jkGuiMods_bInitted )
        return;

    jkGui_InitMenu(&jkGuiMods_menu, jkGui_stdBitmaps[3]);
    jkGuiMods_bInitted = 1;
}

void jkGuiMods_Shutdown()
{
    jkGuiMods_bInitted = 0;
}

void jkGuiMods_Show()
{
    char *v0; // ebx
    char *v1; // ebp
    char *v2; // edx
    wchar_t *v3; // eax
    int v4; // eax
    const char *v6; // eax
    int v7; // esi
    void *i; // eax
    int v9; // [esp+10h] [ebp-15Ch]
    Darray darray; // [esp+14h] [ebp-158h] BYREF
    char v11[64]; // [esp+2Ch] [ebp-140h] BYREF
    char v12[256]; // [esp+6Ch] [ebp-100h] BYREF

    jkGuiMods_aElements[4].wstr = openjkdf2_waReleaseVersion;
    jkGuiMods_aElements[5].wstr = openjkdf2_waReleaseCommitShort;

    jkGui_SetModeMenu(jkGui_stdBitmaps[0]->palette);
    jkGuiRend_DarrayNewStr(&darray, 32, 1);
    
    jkGuiMods_PopulateEntries(&darray, &jkGuiMods_aElements[1]);

    v4 = -1;
    do
    {
        jkGuiRend_MenuSetReturnKeyShortcutElement(&jkGuiMods_menu, &jkGuiMods_aElements[2]);
        jkGuiRend_MenuSetEscapeKeyShortcutElement(&jkGuiMods_menu, &jkGuiMods_aElements[3]);
        v4 = jkGuiRend_DisplayAndReturnClicked(&jkGuiMods_menu);
        
        if (v4 == JKGUIMODS_BTN_OPENRESOURCEFOLDER) {
#ifdef SDL2_RENDER
            char tmpCwd[256];
            char tmpUrl[512];
            getcwd(tmpCwd, sizeof(tmpCwd));
            snprintf(tmpUrl, sizeof(tmpUrl), "file://%s", tmpCwd);

            SDL_ClearError();
            int error = jkGuiMods_OpenURL(tmpUrl);
#endif
        }
        else if ( v4 == JKGUIMODS_BTN_LISTCLICK )
        {
            jkGuiModsElement_t* pListElement = (jkGuiModsElement_t*)jkGuiRend_GetId(&darray, jkGuiMods_aElements[1].selectedTextEntry);
            snprintf(v12, 256, "mods%c%s", '\\', pListElement->paPath); // Added: sprintf -> snprintf

            printf("Selected entry %u, %s\n", jkGuiMods_aElements[1].selectedTextEntry, v12);
            if (!strcmp(pListElement->paPath, "OPENJKDF2_RESTART_DF2"))
            {
                g_should_exit = 1;
                openjkdf2_restartMode = OPENJKDF2_RESTART_DF2;
                break;
            }
            else if (!strcmp(pListElement->paPath, "OPENJKDF2_RESTART_MOTS"))
            {
                g_should_exit = 1;
                openjkdf2_restartMode = OPENJKDF2_RESTART_MOTS;
                break;
            }
        }
    }
    while ( v4 != -1 );

    v7 = 0;
    for ( i = (void *)jkGuiRend_GetId(&darray, 0); i; i = (void *)jkGuiRend_GetId(&darray, v7) )
    {
        pHS->free(i);
        ++v7;
    }
}

void jkGuiMods_AddEntry(Darray *pListDisplayed, jkGuiElement *pElement, const char* paVal, const char* paDisplayed)
{
    size_t alloc_sz = (_strlen(paDisplayed) + 1) * sizeof(wchar_t);

    wchar_t* out = (wchar_t *)pHS->alloc(alloc_sz);
    memset(out, 0, alloc_sz);

    jkGuiModsElement_t* pListElement = (jkGuiModsElement_t*)pHS->alloc(sizeof(jkGuiModsElement_t));
    memset(pListElement, 0, sizeof(jkGuiModsElement_t));
    pListElement->paPath = paVal;

    stdString_CharToWchar(out, paDisplayed, _strlen(paDisplayed));
    jkGuiRend_DarrayReallocStr(pListDisplayed, out, (intptr_t)pListElement);
    pHS->free(out);
}

void jkGuiMods_PopulateEntries(Darray *pListDisplayed, jkGuiElement *element)
{
    char tmpCwd[512];
    char tmpKeyPath[512];

#ifndef ARCH_WASM
    Main_bMotsCompat = !Main_bMotsCompat;
    InstallHelper_GetLocalDataDir(tmpCwd, sizeof(tmpCwd), 0);
    Main_bMotsCompat = !Main_bMotsCompat;
#else
    strcpy(tmpCwd, ".");
#endif

    
    stdFnames_MakePath(tmpKeyPath, 256, tmpCwd, "resource/jk_.cd");
    int keyval = jkRes_ReadKeyFromFile(tmpKeyPath);

    if (!Main_bMotsCompat)
    {
        if (!(!openjkdf2_bOrigWasDF2 && openjkdf2_bOrigWasRunningFromExistingInstall) && (keyval == 0 || !JKRES_IS_MOTS_MAGIC(keyval))) {
            jkGuiMods_AddEntry(pListDisplayed, element, "OPENJKDF2_RESTART_MOTS", "Install Mysteries of the Sith");
        }
        else {
            jkGuiMods_AddEntry(pListDisplayed, element, "OPENJKDF2_RESTART_MOTS", "Launch Mysteries of the Sith");
        }
    }
    else
    {
        if (!(openjkdf2_bOrigWasDF2 && openjkdf2_bOrigWasRunningFromExistingInstall) && (keyval == 0 || !JKRES_IS_DF2_MAGIC(keyval))) {
            jkGuiMods_AddEntry(pListDisplayed, element, "OPENJKDF2_RESTART_DF2", "Install Dark Forces II");
        }
        else {
            jkGuiMods_AddEntry(pListDisplayed, element, "OPENJKDF2_RESTART_DF2", "Launch Dark Forces II");
        }
    }
    

    stdFileSearchResult modResult;
    stdFileSearch* pSearch = stdFileUtil_NewFind("mods", 3, JKRES_GOB_EXT);
    while (stdFileUtil_FindNext(pSearch, &modResult))
    {
        if ( modResult.fpath[0] != '.' )
        {
            jkGuiMods_AddEntry(pListDisplayed, element, modResult.fpath, modResult.fpath);
        }
    }

    jkGuiRend_AddStringEntry(pListDisplayed, 0, 0);
    jkGuiRend_SetClickableString(element, pListDisplayed);
    element->selectedTextEntry = 0;
}