/* See LICENSE file for copyright and license details. */

/*
 * Keys:
 * $ locate keysymdef.h
 * xev: 
 *
 * */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const Bool showsystray       = True;     /* False means no systray */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
#define MAX_TAGLEN 16
static char tags[][MAX_TAGLEN] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
	/*{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },*/
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* (empty gaps) True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY|ShiftMask,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ControlMask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, "-l", "10", NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *browsercmd[]  = { "google-chrome", NULL };
//static const char *filemanagercmd[]  = { "terminator", "-e", "ranger", NULL };
static const char *filemanagercmd[]  = { "nautilus", "--no-desktop", NULL };
static const char *cmdkilldwm[]  = { "killall", "dwm", NULL };
/* Sound stuff */
#define KEY_SOUND_UP 0x1008ff13
#define KEY_SOUND_DOWN 0x1008ff11
#define KEY_SOUND_TOGGLE 0x1008ff12
/* Custom keys */
#define KEY_PRINT 0xff61
#define KEY_WIN 0xffeb

static const char *cmdsoundup[]  = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *cmdsounddown[]  = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *cmdsoundtoggle[]  = { "amixer", "-q", "sset", "Master", "toggle", NULL };


/* Scripts */
static const char *cmdKB[]  = { "dwm-switch-keyboard", NULL, NULL };
static const char *cmdopenbrowser[]  = { "dwm-open-browser", NULL };
static const char *cmddwmmenu[]  = { "dwm-menu", NULL };
static const char *cmdscreenshot[]  = { "screenshot", "-i", NULL };
/* DPMS - wake lock (dwm-panel needed) */
static const char *cmdtogglewakelock[]  = { "service", "dwm-panel", "toggle", "wakelock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ 0,             KEY_PRINT, spawn,          {.v = termcmd } },
	{ 0,             KEY_WIN, spawn,          {.v = browsercmd } },
	{ MODKEY,             KEY_PRINT,      spawn,          {.v = filemanagercmd} },
	{ MODKEY,             XK_c,      spawn,          {.v = cmdopenbrowser } },
	{ MODKEY|ShiftMask,   XK_m,      spawn,          {.v = cmddwmmenu } },
	{ MODKEY|ShiftMask,   XK_w,      spawn,          {.v = cmdtogglewakelock } },
	{ MODKEY,   XK_q,      spawn,          {.v = cmdKB } },
	{ MODKEY|ShiftMask,   XK_s,      spawn,          {.v = cmdscreenshot } },
	/* Sound */
	{ MODKEY,                            XK_Up,     spawn,         {.v = cmdsoundup } },
	//{ 0,                            KEY_SOUND_UP,     spawn,         {.v = cmdsoundup } },
	{ MODKEY,                            XK_Down,   spawn,         {.v = cmdsounddown } },
	//{ 0,                            KEY_SOUND_DOWN,   spawn,         {.v = cmdsounddown } },
	{ 0,                            KEY_SOUND_TOGGLE, spawn,         {.v = cmdsoundtoggle } },
	/* Killing dwm */
	{ MODKEY|ShiftMask,             XK_q,      spawn,           {.v = cmdkilldwm} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_n,      nametag,        {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	// Restart thanks to dwm-personalized
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
    // kill window
	{ ClkWinTitle,          0,              Button3,        killclient,     {0} },
    // dmenu
	{ ClkWinTitle,          0,              Button1,        spawn,          {.v = dmenucmd} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

