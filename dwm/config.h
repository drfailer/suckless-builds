/* See LICENSE file for copyright and license details. */

/*****************************************************************************/
/* General Settings:                                                         */
/*****************************************************************************/
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {
	"ProFont for Powerline:size=12",
	"JoyPixels:pixelsize=10:antialias=true:autohint=true"
};
static const char dmenufont[]       = "ProFont for Powerline:size=12";
static const char col_gray1[]       = "#1d2021";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#bfbaba";
// static const char col_cyan[]        = "#306edc";
// static const char col_cyan[]        = "#003B6F";
static const char col_cyan[]        = "#006699";
static const char col_border[]      = "#458588";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1  },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border },
};

/*****************************************************************************/
/* Tags:                                                                     */
/*****************************************************************************/
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/*****************************************************************************/
/* Tags's rules:                                                             */
/*****************************************************************************/
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Discord",  NULL,       NULL,       0,            0,            0 },
};

/*****************************************************************************/
/* Layouts:                                                                  */
/*****************************************************************************/
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.00; /* factor of tiled clients [0.00..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/*****************************************************************************/
/* Key definitions:                                                          */
/*****************************************************************************/
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN, KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN, KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN, KEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN, KEY, toggletag,  {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/*****************************************************************************/
/* Commands:                                                                 */
/*****************************************************************************/
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn",
	dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf",
	col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *ranger[] = { "st -e ranger", NULL };
static const char *search[] = {
	"/home/drfailer/.config/suckless-builds/dmenu-scripts/search/search", NULL };
static const char *sound[] = {
	"/home/drfailer/.config/suckless-builds/dmenu-scripts/sound/sound", NULL };
static const char *bright[] = {
	"/home/drfailer/.config/suckless-builds/dmenu-scripts/brightness/brightness", NULL };
static const char *enote[] = {
	"/home/drfailer/.config/suckless-builds/dmenu-scripts/notes/edit-notes", NULL };
static const char *rnote[] = {
	"/home/drfailer/.config/suckless-builds/dmenu-scripts/notes/read-note", NULL };

/*****************************************************************************/
/* Keyboard:                                                                 */
/*****************************************************************************/
static Key keys[] = {
 	/* modifier        chain key   key        function                argument */
	/***************************************************************************/
	/* General:                                                                */
	/***************************************************************************/
 	{ MODKEY,            -1,       XK_p,      spawn,          {.v = dmenucmd } },
 	{ MODKEY|ShiftMask,  -1,       XK_Return, spawn,           {.v = termcmd } },
 	{ MODKEY,            -1,       XK_b,      togglebar,                   {0} },
	/***************************************************************************/
	/* Windows manipulations:                                                  */
	/***************************************************************************/
 	{ MODKEY,            -1,       XK_j,      focusstack,            {.i = +1 } },
 	{ MODKEY,            -1,       XK_k,      focusstack,            {.i = -1 } },
 	{ MODKEY,            -1,       XK_i,      incnmaster,            {.i = +1 } },
 	{ MODKEY,            -1,       XK_d,      incnmaster,            {.i = -1 } },
 	{ MODKEY,            -1,       XK_h,      setmfact,              {.f = -0.05} },
 	{ MODKEY,            -1,       XK_l,      setmfact,              {.f = +0.05} },
 	{ MODKEY|ShiftMask,  -1,       XK_k,      setsmfact,             {.f = +0.05} },
 	{ MODKEY|ShiftMask,  -1,       XK_j,      setsmfact,             {.f = -0.05} },
 	{ MODKEY,            -1,       XK_Return, zoom,                  {0} },
 	{ MODKEY,            -1,       XK_Tab,    view,                  {0} },
 	{ MODKEY|ShiftMask,  -1,       XK_c,      killclient,            {0} },
	/***************************************************************************/
	/* Layouts:                                                                */
	/***************************************************************************/
	{ MODKEY|ShiftMask,  XK_l,     XK_t,      setlayout,      {.v = &layouts[0]} },
 	{ MODKEY|ShiftMask,  XK_l,     XK_m,      setlayout,      {.v = &layouts[1]} },
 	{ MODKEY|ShiftMask,  XK_l,     XK_u,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,  XK_l,     XK_o,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,  XK_l,     XK_f,      setlayout,      {.v = &layouts[4]} },
 	{ MODKEY,              -1,     XK_space,  setlayout,      {0} },
 	{ MODKEY|ShiftMask,    -1,     XK_space,  togglefloating, {0} },
	/***************************************************************************/
	/* Screen Manipulation:                                                    */
	/***************************************************************************/
 	{ MODKEY,              -1,     XK_agrave,        view,         {.ui = ~0 } },
 	{ MODKEY|ShiftMask,    -1,     XK_agrave,         tag,         {.ui = ~0 } },
 	{ MODKEY,              -1,     XK_comma,     focusmon,          {.i = -1 } },
 	{ MODKEY,              -1,     XK_semicolon, focusmon,          {.i = +1 } },
 	{ MODKEY|ShiftMask,    -1,     XK_comma,       tagmon,          {.i = -1 } },
 	{ MODKEY|ShiftMask,    -1,     XK_semicolon,   tagmon,          {.i = +1 } },
	/***************************************************************************/
	/* Gaps:                                                                   */
	/***************************************************************************/
 	{ MODKEY,              -1,     XK_minus,     setgaps,           {.i = -1 } },
 	{ MODKEY,              -1,     XK_equal,     setgaps,           {.i = +1 } },
 	{ MODKEY|ShiftMask,    -1,     XK_equal,     setgaps,           {.i = 0  } },
	/***************************************************************************/
	/* Tags:                                                                   */
	/***************************************************************************/
 	TAGKEYS(               -1,     XK_ampersand,                        0)
 	TAGKEYS(               -1,     XK_eacute,                           1)
 	TAGKEYS(               -1,     XK_quotedbl,                         2)
 	TAGKEYS(               -1,     XK_apostrophe,                       3)
 	TAGKEYS(               -1,     XK_parenleft,                        4)
 	TAGKEYS(               -1,     XK_minus,                            5)
 	TAGKEYS(               -1,     XK_egrave,                           6)
 	TAGKEYS(               -1,     XK_underscore,                       7)
 	TAGKEYS(               -1,     XK_ccedilla,                         8)
 	{ MODKEY|ShiftMask,    -1,     XK_q,         quit,                 {0} },
	/***************************************************************************/
	/* Applications:                                                           */
	/***************************************************************************/
 	{ MODKEY,            XK_a,     XK_d,       spawn,         {.v = dmenucmd } },
 	{ MODKEY,            XK_a,     XK_t,       spawn,         {.v = termcmd  } },
 	{ MODKEY,              -1,     XK_d,       spawn,         {.v = ranger   } },
	/***************************************************************************/
	/* dmenu scripts:                                                          */
	/***************************************************************************/
 	{ MODKEY|ShiftMask,  XK_n,     XK_e,      spawn,          {.v = enote } },
 	{ MODKEY|ShiftMask,  XK_n,     XK_r,      spawn,          {.v = rnote } },
 	{ MODKEY|ShiftMask,  XK_p,     XK_s,      spawn,          {.v = sound } },
 	{ MODKEY|ShiftMask,  XK_p,     XK_b,      spawn,          {.v = bright } },
 	{ MODKEY,              -1,     XK_f,      spawn,          {.v = search } },
};

/*****************************************************************************/
/* Mouse:                                                                    */
/*****************************************************************************/
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

