enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab                   = showtab_never; /* Default tab bar show mode */
static const int toptab                    = 0; /* False means bottom tab bar */
static       int showpreview               = 0; /* show tag preview */
static const int scalepreview              = 4; /* tag preview scaling */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const int horizpadbar               = 0; /* horizontal padding for statusbar */
static const int vertpadbar                = 0; /* vertical padding for statusbar */
static const int vertpad                   = 0; /* vertical padding of bar */
static const int sidepad                   = 0; /* horizontal padding of bar */
static const int vertpadtoggle             = vertpad ? vertpad : 10; /* vertical padding of bar that's toggleable */
static const int sidepadtoggle             = sidepad ? sidepad : 10; /* horizontal padding of bar that's toggleable */
static const int user_bh                   = 24; /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int systraypinning   = 1;  /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing   = 2;  /* systray spacing */
static const int systraypinningfailfirst   = 1;  /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray               = 1;  /* 0 means no systray */
static       unsigned int vacantonstart    = 1;  /* 0 means no vacant tags */
static const unsigned int ulinepad         = 6;  /* horizontal padding between the underline and tag */
static const unsigned int ulinestroke      = 2;  /* thickness / height of the underline */
static const unsigned int ulinevoffset     = 0;  /* how far above the bottom of the bar the line should appear */
static const unsigned int underlinetags    = 1;  /* 0 means no underline */
static const unsigned int underlinevacant  = 1;  /* 0 means no underline for vacant tags */
static const unsigned int gappih           = vertpad || sidepad ? vertpadtoggle : 0; /* horiz inner gap between windows */
static const unsigned int gappiv           = vertpad || sidepad ? vertpadtoggle : 0; /* vert inner gap between windows */
static const unsigned int gappoh           = vertpad            ? sidepadtoggle : 0; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov           = sidepad            ? sidepadtoggle : 0; /* vert outer gap between windows and screen edge */
static       unsigned int smartgaps        = vertpad || sidepad ? 0 : 1; /* 1 means no outer gap when there is only one window one window */
static       unsigned int padding          = vertpad || sidepad ? 1 : 0;
static const int swallowfloating           = 1; /* 1 means swallow floating windows by default */
static unsigned int borderpx               = 1; /* border pixel of windows */
static unsigned int floatborderpx          = 2; /* border pixel of floating windows */
static const unsigned int snap             = 0; /* snap pixel */
static const int startontag                = 1; /* 0 means no tag active on start */
static const int decorhints                = 1; /* 1 means respect decoration hints */
static const int focusonwheel              = 0;
static const char *fonts[] = { "Iosevka Nerd Font:pixelsize=14:antialias=true:autohint=true" };

static const char normfg[]                = "#4E5579";
static const char selfg[]                 = "#5fafff";
static const char normbg[]                = "#1E1C31";
static const char selbg[]                 = "#1E1C31";

static const char invnormbg[]             = "#f0f0f0";
static const char invnormfg[]             = "#000000";
static const char invselfg[]              = "#5fafff";
static const char invselbg[]              = "#f0f0f0";

static const char normfloatwinborder[]    = "#0f111b";
static const char selfloatwinborder[]     = "#81a1c1";
static const char normstickyborder[]      = "#0f111b";
static const char selstickyborder[]       = "#98be65";
static const char normstickyfloatborder[] = "#0f111b";
static const char selstickyfloatborder[]  = "#8acc35";
static const char normfakefullscr[]       = "#408ab2";
static const char selfakefullscr[]        = "#b869e5";
static const char normfakefullscrfloat[]  = "#289fe0";
static const char selfakefullscrfloat[]   = "#9b1be5";

static const char occupiedfg[]            = "#7986E7";
static const char occupiedbg[]            = "#1E1C31";

static const char ocinvfg[]               = "#7986E7";
static const char ocinvbg[]               = "#f0f0f0";

static const char statusfg[]              = "#7986E7";
static const char statusbg[]              = "#1e1c31";

static const char invstatusbg[]           = "#f0f0f0";

static const char ltsymbolfg[]            = "#1e1c31";
static const char ltsymbolbg[]            = "#81a1c1";

static const char normtabfg[]             = "#4E5579";
static const char seltabfg[]              = "#7986E7";
static const char normtabbg[]             = "#1E1C31";
static const char seltabbg[]              = "#1E1C31";

static const char vacindfg[]              = "#4e5579";
static const char indfg[]                 = "#7986E7";

static const char numfg[]                 = "#7986e7";
static const char numbg[]                 = "#1e1c31";

static const char systraybg[]             = "#1E1C31";

static const char normtileborder[]        = "#1E1C31";
static const char normfibonacciborder[]   = "#1E1C31";
static const char normfloatborder[]       = "#1E1C31";
static const char normdeckborder[]        = "#1E1C31";
static const char normnrowgridborder[]    = "#1E1C31";
static const char normbstackborder[]      = "#1E1C31";
static const char normcenmasterborder[]   = "#1E1C31";
static const char normmonocleborder[]     = "#1E1C31";
static const char normgaplessgridborder[] = "#1E1C31";
static const char seltileborder[]         = "#5fafff";
static const char selfibonacciborder[]    = "#5fafff";
static const char selfloatborder[]        = "#5fafff";
static const char seldeckborder[]         = "#5fafff";
static const char selnrowgridborder[]     = "#5fafff";
static const char selbstackborder[]       = "#5fafff";
static const char selcenmasterborder[]    = "#5fafff";
static const char selmonocleborder[]      = "#5fafff";
static const char selgaplessgridborder[]  = "#5fafff";

static const char *colors[][10]  = {
    /* Tags/borders       fg            bg      float               sticky            sticky + float         fakefullscreen   fakefullscreen + float */
    [SchemeNorm]        = { normfg,     normbg, normfloatwinborder, normstickyborder, normstickyfloatborder, normfakefullscr, normfakefullscrfloat },
    [SchemeSel]         = { selfg,      selbg,  selfloatwinborder,  selstickyborder,  selstickyfloatborder,  selfakefullscr,  selfakefullscrfloat },
    [SchemeOccupied]    = { occupiedfg, occupiedbg },
    [SchemeOccupiedInv] = { ocinvfg,    ocinvbg },
    [SchemeStatus]      = { statusfg,   statusbg, invstatusbg },
    [SchemeLtsymbol]    = { ltsymbolfg, ltsymbolbg },
    [SchemeTabNorm]     = { normtabfg,  normtabbg },
    [SchemeTabSel]      = { seltabfg,   seltabbg},
    [SchemeClientVac]   = { vacindfg },
    [SchemeClient]      = { indfg },
    [SchemeClientNum]   = { numfg,      numbg },
    [SchemeSystray]     = {             systraybg },
    [SchemeInvMon]      = { invnormfg,  invnormbg },
    [SchemeInvMonSel]   = { invselfg,   invselbg },
    /* Win borders          tile            fibonacci            float            deck            nrowgrid            bstack            centeredmaster       monocle            gaplessgrid */
    [SchemeNormLayout]  = { normtileborder, normfibonacciborder, normfloatborder, normdeckborder, normnrowgridborder, normbstackborder, normcenmasterborder, normmonocleborder, normgaplessgridborder },
    [SchemeSelLayout]   = { seltileborder,  selfibonacciborder,  selfloatborder,  seldeckborder,  selnrowgridborder,  selbstackborder,  selcenmasterborder,  selmonocleborder,  selgaplessgridborder },
};

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char ptagf[] = "[%s:%s]";
static const char etagf[] = "%s";
static const int lcaselbl = 0;

/*
static const char *scpclean[] = {"u", NULL};
static const char *scpcmus[]  = {"i", "st", "-c", "scpcmus",  "-t", "cmusSCP", "-e", "cmus", NULL};
*/
static const char *scpranger[]   = {"u", "st", "-c", "Ranger", "-t", "Ranger", "-g", "144x41", "-e", "ranger", NULL};
static const char *scpterm[] = { "i", "st", "-c", "scpterm", "-t", "scpterm", "-g", "144x41", NULL };

#define WTYPE "_NET_WM_WINDOW_TYPE_"

static const Rule rules[] = {
    /* class      instance    title          wintype tags mask switchtotag isfloating iscentered ispermanent isterminal noswallow monitor scratch key */
    /* Scratchpads */
    { NULL,       NULL,      "Ranger",      NULL,   0,        0,          1,         1,         0,          1,         0,        -1, 'u' },
    { NULL,       NULL,      "scpterm",     NULL,   0,        0,          1,         1,         0,          1,         0,        -1, 'i' },
    /*
    { "scpclean", NULL,       NULL,          NULL,   0,        0,          0,         0,         0,          0,         0,        -1, 'u' },
    { "scpcmus",  NULL,       NULL,          NULL,   0,        0,          0,         0,         1,          0,         0,        -1, 'i' },
    { NULL,       NULL,       "calSCP",      NULL,   0,        0,          1,         1,         0,          0,         0,        -1, 'y' },
    */
    /* Swallow */
    { "St",       NULL,       NULL,          NULL,   0,        0,          0,         0,         0,          1,         0,        -1, 0 },
    { "Alacritty",NULL,       NULL,          NULL,   0,        0,          0,         0,         0,          1,         0,        -1, 0 },
    { "XTerm",    NULL,       NULL,          NULL,   0,        0,          0,         0,         0,          1,         0,        -1, 0 },
    { "Emacs",    NULL,       NULL,          NULL,   0,        0,          0,         0,         0,          1,         0,        -1, 0 },
    /* Noswallow */
    { NULL,       NULL,       "Event Tester",NULL,   0,        0,          0,         0,         0,          0,         1,        -1, 0 },
    { "Xephyr",   NULL,       NULL,          NULL,   0,        0,          1,         1,         0,          0,         1,        -1, 0 },
    { "Gimp",     NULL,       NULL,          NULL,   1 << 8,   3,          1,         1,         0,          0,         1,        -1, 0 },
    { NULL,       NULL,       "glxgears",    NULL,   0,        0,          1,         0,         0,          0,         1,        -1, 0 },
    /* General windows */
    { NULL,       "Navigator",NULL,          NULL,   1,        0,          0,         0,         1,          0,         1,        -1, 0 },
    { NULL,       "chromium", NULL,          NULL,   1 << 3,   0,          0,         0,         1,          0,         1,        -1, 0 },
    { NULL,       "spotify",  NULL,          NULL,   1 << 6,   0,          0,         0,         0,          0,         0,        -1, 0 },
    { NULL,       "discord",  NULL,          NULL,   1 << 7,   0,          0,         0,         0,          0,         0,        -1, 0 },
    /* Wintype */
    { NULL,       NULL,       NULL, WTYPE "DIALOG",  0,        0,          1,         1,         0,          0,         0,        -1, 0 },
    { NULL,       NULL,       NULL, WTYPE "UTILITY", 0,        0,          1,         1,         0,          0,         0,        -1, 0 },
    { NULL,       NULL,       NULL, WTYPE "TOOLBAR", 0,        0,          1,         1,         0,          0,         0,        -1, 0 },
    { NULL,       NULL,       NULL, WTYPE "SPLASH",  0,        0,          1,         1,         0,          0,         0,        -1, 0 },
};

static const TagRule tagrules[LENGTH(tags) + 1] = {
    /* showbar topbar vacant layout gapih gapiv gapoh gapov smartgaps vpad spad borderpx nmaster mfact */
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  1,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   1,       1,      0.5 },
    {  0,      1,     1,     0,     0,    0,    0,    0,    1,        0,   0,   0,       1,      0.5 },
};

static const float mfact     = 0.5;
static const int resizehints = 0;
static const int nmaster     = 1;
static const int attachbelow = 1;

#define FORCE_VSPLIT 1
#include "vanitygaps.c"

static const Layout layouts[] = {
    /* symbol           arrange function */
    { "tile",           tile },
    { "spiral",         spiral },
    { "float",          NULL },
    { "deck",           deck },
    { "nrowgrid",       nrowgrid },
    { "bstack",         bstack },
    { "centeredmaster", centeredmaster },
    { "monocle",        monocle },
    { "grid",           gaplessgrid },
    { NULL,             NULL },
};

#include <X11/XF86keysym.h>

#define M Mod4Mask
#define A Mod1Mask
#define S ShiftMask
#define C ControlMask

#define TAGKEYS(KEY,TAG) \
    {1, {{M,     KEY}},                 view,          {.ui = 1 << TAG } }, \
    {1, {{C,     KEY}},                 toggleview,    {.ui = 1 << TAG } }, \
    {1, {{A,     KEY}},                 toggletag,     {.ui = 1 << TAG } }, \
    {1, {{A|S,   KEY}},                 combotag,      {.ui = 1 << TAG } }, \
    {1, {{A|C,   KEY}},                 tagwith,       {.ui = 1 << TAG } }, \
    {1, {{M|S,   KEY}},                 swaptags,      {.ui = 1 << TAG } }, \
    {2, {{A|C,   XK_q},      {0, KEY}}, killontag,     {.ui = 1 << TAG } }, \
    {2, {{A|C,   XK_comma},  {0, KEY}}, focusprevmon,  {.ui = 1 << TAG } }, \
    {2, {{A|C,   XK_period}, {0, KEY}}, focusnextmon,  {.ui = 1 << TAG } }, \
    {2, {{A|C|S, XK_comma},  {0, KEY}}, tagprevmon,    {.ui = 1 << TAG } }, \
    {2, {{A|C|S, XK_period}, {0, KEY}}, tagnextmon,    {.ui = 1 << TAG } },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

Keychord keychords[] = {
{1, {{M,      XK_Return}},               spawn,                SHCMD("$TERMINAL") },
{1, {{A|S,    XK_c     }},               spawn,                SHCMD("$TERMINAL htop") },
{1, {{A|S,    XK_z     }},               spawn,                SHCMD("playerctl play-pause") },
{1, {{M,      XK_w}},                    spawn,                SHCMD("xdo activate -N google-chrome-stable || google-chrome-stable") },
{1, {{C|S,    XK_Escape}},               spawn,                SHCMD("xkill") },
{1, {{A|C,    XK_d}},                    spawn,                SHCMD("discord") },
{1, {{M,      XK_p}},                    spawn,                SHCMD("thunar") },
{1, {{A|C,    XK_m}},                    spawn,                SHCMD("multimc") },
{1, {{A|M|C,  XK_l}},                    spawn,                SHCMD("slock") },
{1, {{M|S,    XK_Return}},               spawn,                SHCMD("rofi -show drun") },
{1, {{M,      XK_Tab}},                  spawn,                SHCMD("rofi -show") },
{1, {{A,      XK_c}},                    spawn,                SHCMD("volume-script") },

/*
{1, {{A,      XK_Down}},               moveresize,             {.v = "0x 25y 0w 0h" } },
{1, {{A,      XK_Up}},                 moveresize,             {.v = "0x -25y 0w 0h" } },
{1, {{A,      XK_Right}},              moveresize,             {.v = "25x 0y 0w 0h" } },
{1, {{A,      XK_Left}},               moveresize,             {.v = "-25x 0y 0w 0h" } },
{1, {{A|S,    XK_Down}},               moveresize,             {.v = "0x 0y 0w 25h" } },
{1, {{A|S,    XK_Up}},                 moveresize,             {.v = "0x 0y 0w -25h" } },
{1, {{A|S,    XK_Right}},              moveresize,             {.v = "0x 0y 25w 0h" } },
{1, {{A|S,    XK_Left}},               moveresize,             {.v = "0x 0y -25w 0h" } },
{1, {{C|A,		XK_Down}},               moveresize,             {.v = "0x 1y 0w 0h" } },
{1, {{C|A,    XK_Up}},                 moveresize,             {.v = "0x -1y 0w 0h" } },
{1, {{C|A,    XK_Right}},              moveresize,             {.v = "1x 0y 0w 0h" } },
{1, {{C|A,    XK_Left}},               moveresize,             {.v = "-1x 0y 0w 0h" } },
{1, {{C|A|S,  XK_Down}},               moveresize,             {.v = "0x 0y 0w 1h" } },
{1, {{C|A|S,  XK_Up}},                 moveresize,             {.v = "0x 0y 0w -1h" } },
{1, {{C|A|S,  XK_Right}},              moveresize,             {.v = "0x 0y 1w 0h" } },
{1, {{C|A|S,  XK_Left}},               moveresize,             {.v = "0x 0y -1w 0h" } },
*/

/*
{1, {{M,      XK_g}},                    spawn,                SHCMD("xmenu.sh -p 0x0") },
{1, {{A,      XK_s}},                    spawn,                SHCMD("~/.emacs.d/bin/doom everywhere") },
{1, {{A|C,    XK_s}},                    spawn,                SHCMD("spotify") },
{1, {{A|C,    XK_u}},                    spawn,                SHCMD("import my-stuff/Pictures/snips/$(date +'%F-%T').png") },
{1, {{M,      XK_w}},                    spawn,                SHCMD("xdo activate -N Chromium || chromium") },
{1, {{A|C,    XK_Return}},               spawn,                SHCMD("Booky 'st -e nvim' '><' 'Cconfig'") },
{1, {{A|S,    XK_w}},                    spawn,                SHCMD("Booky 'firefox' '_' 'Bconfig'") },
{1, {{A,      XK_z}},                    spawn,                SHCMD("cmus-rem") },
{2, {{A|S,    XK_d}, {0, XK_s}},         spawn,                SHCMD("switch") },
{2, {{A|S,    XK_d}, {0, XK_c}},         spawn,                SHCMD("calc") },
{2, {{A|S,    XK_d}, {0, XK_p}},         spawn,                SHCMD("passmenu2 -F -p 'Passwords:'") },
{2, {{A|S,    XK_d}, {0, XK_m}},         spawn,                SHCMD("manview") },
{2, {{A|S,    XK_d}, {0, XK_q}},         spawn,                SHCMD("shut") },
{1, {{0,      XF86XK_AudioPrev}},        spawn,                SHCMD("playerctl --player cmus previous") },
{1, {{0,      XF86XK_AudioNext}},        spawn,                SHCMD("playerctl --player cmus next") },
{1, {{0,      XF86XK_AudioPlay}},        spawn,                SHCMD("playerctl --player cmus play-pause") },
{1, {{0,      XF86XK_AudioLowerVolume}}, spawn,                SHCMD("pamixer --allow-boost -d 1 ; sdwm -v") },
{1, {{0,      XF86XK_AudioRaiseVolume}}, spawn,                SHCMD("pamixer --allow-boost -i 1 ; sdwm -v") },
*/
{1, {{M,      XK_q}},                    killclient,           {0} },
{1, {{A|C|S,  XK_x}},                    killpermanent,        {0} },
{1, {{A|S,    XK_q}},                    killunsel,            {0} },
{1, {{M,      XK_v}},                    togglevacant,         {0} },
{1, {{A|C,    XK_v}},                    toggletopbar,         {0} },
{1, {{M|S,    XK_v}},                    togglepadding,        {0} },
{1, {{A|S,    XK_p}},                    togglepreview,        {0} },
{1, {{A,      XK_n}},                    togglebar,            {0} },
{1, {{A|S,    XK_h}},                    setmfact,             { .f = -0.05 } },
{1, {{A|S,    XK_l}},                    setmfact,             { .f = +0.05 } },
{1, {{M|C,    XK_u}},                    setmfact,             { .f = mfact + 1 } },
{1, {{A|S,    XK_j}},                    setcfact,             { .f = +0.25 } },
{1, {{A|S,    XK_k}},                    setcfact,             { .f = -0.25 } },
{1, {{M|C|S,  XK_u}},                    setcfact,             {0} },
{1, {{A,      XK_bracketleft}},          incnmaster,           { .i = +1 } },
{1, {{A,      XK_bracketright}},         incnmaster,           { .i = -1 } },
{1, {{M,      XK_space}},                focusmaster,          {0} },
{1, {{A|C,    XK_space}},                switchcol,            {0} },
{1, {{M,      XK_h}},                    focusdir,             { .i = 0 } },
{1, {{M,      XK_l}},                    focusdir,             { .i = 1 } },
{1, {{M,      XK_k}},                    focusdir,             { .i = 2 } },
{1, {{M,      XK_j}},                    focusdir,             { .i = 3 } },
{1, {{M|S,    XK_j}},                    focusstack,           { .i = +1 } },
{1, {{M|S,    XK_k}},                    focusstack,           { .i = -1 } },
{1, {{A,      XK_t}},                    setlayout,            { .v = &layouts[0] }},
{1, {{A,      XK_v}},                    setlayout,            { .v = &layouts[1] }},
{1, {{A|S,    XK_f}},                    setlayout,            { .v = &layouts[2] }},
{1, {{A,      XK_d}},                    setlayout,            { .v = &layouts[3] }},
{1, {{A,      XK_g}},                    setlayout,            { .v = &layouts[4] }},
{1, {{A,      XK_b}},                    setlayout,            { .v = &layouts[5] }},
{1, {{A|S,    XK_m}},                    setlayout,            { .v = &layouts[6] }},
{1, {{A,      XK_m}},                    setlayout,            { .v = &layouts[7] }},
{1, {{A|S,    XK_g}},                    setlayout,            { .v = &layouts[8] }},
{1, {{A|S,    XK_t}},                    tabmode,              {-1} },
{1, {{A|C,    XK_i}},                    cyclelayout,          { .i = -1 } },
{1, {{A|C,    XK_p}},                    cyclelayout,          { .i = +1 } },
{1, {{A,      XK_Tab}},                  goback,               {0} },
{1, {{A|S,    XK_bracketright}},         viewnext,             {0} },
{1, {{A|S,    XK_bracketleft}},          viewprev,             {0} },
{1, {{A|S,    XK_a}},                    winview,              {0} },
{1, {{A,      XK_semicolon}},            zoom,                 {0} },
{1, {{A|S,    XK_v}},                    transfer,             {0} },
{1, {{M|C,    XK_j}},                    pushdown,             {0} },
{1, {{M|C,    XK_k}},                    pushup,               {0} },
{1, {{A|C,    XK_r}},                    togglefloating,       {0} },
{1, {{A|S,    XK_space}},                unfloatvisible,       {0} },
{1, {{A|S,    XK_s}},                    togglesticky,         {0} },
{1, {{A,      XK_f}},                    togglefullscr,        {0} },
{1, {{A|C,    XK_f}},                    togglefakefullscreen, {0} },
{1, {{A,      XK_u}},                    togglescratch,        { .v = scpranger } },
{1, {{A|M,    XK_u}},                    removescratch,        { .v = scpranger } },
{1, {{A|S,    XK_u}},                    setscratch,           { .v = scpranger } },
{1, {{A,      XK_i}},                    togglescratch,        { .v = scpterm } },
{1, {{A|M,    XK_i}},                    removescratch,        { .v = scpterm } },
{1, {{A|S,    XK_i}},                    setscratch,           { .v = scpterm } },
/*
{1, {{A,      XK_u}},                    togglescratch,        { .v = scpclean } },
{1, {{A,      XK_i}},                    togglescratch,        { .v = scpcmus } },
{1, {{A,      XK_y}},                    togglescratch,        { .v = scpcal } },
{1, {{A|M,    XK_u}},                    removescratch,        { .v = scpclean } },
{1, {{A|M,    XK_i}},                    removescratch,        { .v = scpcmus } },
{1, {{A|M,    XK_y}},                    removescratch,        { .v = scpcal } },
{1, {{A|S,    XK_u}},                    setscratch,           { .v = scpclean } },
{1, {{A|S,    XK_i}},                    setscratch,           { .v = scpcmus } },
{1, {{A|S,    XK_y}},                    setscratch,           { .v = scpcal } },
*/
{1, {{A,      XK_comma}},                focusmon,             { .i = -1 } },
{1, {{A,      XK_period}},               focusmon,             { .i = +1 } },
{1, {{A|S,    XK_comma}},                tagmon,               { .i = -1 } },
{1, {{A|S,    XK_period}},               tagmon,               { .i = +1 } },
{1, {{A|S,    XK_equal}},                incrgaps,             { .i = +1 } },
{1, {{A|S,    XK_minus}},                incrgaps,             { .i = -1 } },
{1, {{A|S,    XK_0}},                    defaultgaps,          {0} },
{1, {{A|C,    XK_0}},                    togglegaps,           {0} },
{1, {{A|C,    XK_equal}},                setborderpx,          { .i = +1 } },
{1, {{A|C,    XK_minus}},                setborderpx,          { .i = -1 } },
{1, {{M,      XK_0}},                    setborderpx,          { .i = 0 } },
{1, {{M|S,    XK_Escape}},               quit,                 {0} },
{1, {{A|C|S,  XK_q}},                    quit,                 {1} },

TAGKEYS(XK_1, 0)
TAGKEYS(XK_2, 1)
TAGKEYS(XK_3, 2)
TAGKEYS(XK_4, 3)
TAGKEYS(XK_5, 4)
TAGKEYS(XK_6, 5)
TAGKEYS(XK_7, 6)
TAGKEYS(XK_8, 7)
TAGKEYS(XK_9, 8)
/*
TAGKEYS(XK_KP_1, 'A')
TAGKEYS(XK_KP_2, 'B')
TAGKEYS(XK_KP_3, 'C')
TAGKEYS(XK_KP_4, 'D')
TAGKEYS(XK_KP_5, 'E')
TAGKEYS(XK_KP_6, 'F')
TAGKEYS(XK_KP_7, 'G')
TAGKEYS(XK_KP_8, 'H')
TAGKEYS(XK_KP_9, 'I')
*/
};

static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      { .v = &layouts[0] } },
    { ClkLtSymbol,          0,              Button3,        setlayout,      { .v = &layouts[6] } },
    { ClkLtSymbol,          S,              Button1,        cyclelayout,    { .i = +1 } },
    { ClkLtSymbol,          S,              Button3,        cyclelayout,    { .i = -1 } },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            A,              Button1,        tag,            {0} },
    { ClkTagBar,            A,              Button3,        toggletag,      {0} },
    { ClkNumSymbol,         0,              Button1,        spawn,          SHCMD("xmenu.sh -p 0x0") },
    { ClkClientWin,         A,              Button1,        movemouse,      {0} },
    { ClkClientWin,         A,              Button2,        togglefloating, {0} },
    { ClkClientWin,         A,              Button3,        resizemouse,    {0} },
    { ClkClientWin,         A|S,            Button2,        movecenter,     {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

#include "dwmc.c"

static Signal signals[] = {
    /* signum           function */
    { "togglebar",      togglebar },
    { "togglevacant",   togglevacant },
    { "togglepadding",  togglepadding },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "quit",           quit },
    { "viewex",         viewex },
    { "toggleviewex",   toggleviewex },
    { "tagex",          tagex },
    { "tagwithex",      tagwithex },
    { "toggletagex",    toggletagex },
    { "setlayoutex",    setlayoutex },
};