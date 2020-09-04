/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 0;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=8", "FontAwesome:pixelsize=20:antialias=true:autohint=true", "JoyPixels:pixelsize=10:antialias=true:autohint=true"  };
static const char dmenufont[]       = "Inconsolata";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeHid]  = { selbgcolor,  normfgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
   "dwmblocks", NULL,
   NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* launcher commands (They must be NULL terminated) */
static const char* surf[]      = { "surf", "duckduckgo.com", NULL };
static const char* st[]      = { "st", NULL };

static const Launcher launchers[] = {
       /* command       name to display */
	{ surf,         "🦆" },
	{ st,           "st" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "Discord", NULL,     NULL,           0,         0,          0,           0,         1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STCMD(cmd) { .v = (const char*[]){ "st", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };
#include <X11/XF86keysym.h>
#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        			function        		argument */
	{ MODKEY,                       XK_d,      			spawn,				{.v = dmenucmd} },
	{ MODKEY,                       XK_Return, 			spawn,				{.v = termcmd} },
	{ 0,                	  	XF86XK_AudioPrev,   		spawn,				SHCMD("playerctl previous") },
	{ 0,                       	XF86XK_AudioNext,   		spawn,				SHCMD("playerctl next") },
	{ 0,                       	XF86XK_AudioPlay,   		spawn,				SHCMD("playerctl play-pause") },
	{ 0,                       	XF86XK_AudioStop,   		spawn,				SHCMD("playerctl stop") },
	{ 0,                      	XF86XK_AudioMute,   		spawn,				SHCMD("pamixer -t") },
	{ 0,                      	XF86XK_AudioRaiseVolume,	spawn,				SHCMD("pamixer -i 5") },
	{ 0,                      	XF86XK_AudioLowerVolume,	spawn,				SHCMD("pamixer -d 5") },
	{ 0,                      	XK_Print, 	   		spawn,				SHCMD("screenshot.sh") },
	{ MODKEY,                       XK_w,		   		spawn,				SHCMD("surf") },
	{ MODKEY,                       XK_e,		   		spawn,				STCMD("nvim") },
	{ MODKEY,                       XK_r,		   		spawn,				STCMD("ranger") },
	{ MODKEY,                       XK_c,		   		spawn,				STCMD("calcurse") },
	{ MODKEY,                       XK_t,		   		spawn,				STCMD("htop") },
	{ MODKEY,                       XK_n,		   		spawn,				STCMD("newsboat") },
	{ MODKEY|ShiftMask,             XK_m,		   		spawn,				STCMD("ncmpcpp") },
	{ MODKEY,                       XK_m,		   		spawn,				STCMD("neomutt") },
	{ MODKEY|ShiftMask,             XK_w,		   		spawn,				SHCMD("browsers.sh") },
	{ MODKEY|ShiftMask,             XK_p,		   		spawn,				SHCMD("emoji.sh") },
	{ MODKEY,                       XK_b,		   		togglebar,      		{0} },
	{ MODKEY,                       XK_j,		   		focusstack,     		{.i = +1 } },
	{ MODKEY,                       XK_k,		   		focusstack,     		{.i = -1 } },
	{ MODKEY,                       XK_i,		   		incnmaster,     		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,		   		incnmaster,     		{.i = -1 } },
	{ MODKEY,                       XK_h,		   		setmfact,       		{.f = -0.05} },
	{ MODKEY,                       XK_l,		   		setmfact,       		{.f = +0.05} },
   	{ MODKEY|ShiftMask,             XK_j,		   		movestack,      		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,		   		movestack,      		{.i = -1 } },
   	{ MODKEY|ShiftMask,             XK_h,		   		setcfact,       		{.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,		   		setcfact,       		{.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_Return,	   		zoom,           		{0} },
	{ MODKEY,                       XK_Tab,		   		view,           		{0} },
	{ MODKEY|ShiftMask,             XK_q,		   		killclient,     		{0} },
	{ MODKEY,                       XK_t,		   		setlayout,      		{.v = &layouts[0]} },
	{ MODKEY,                       XK_f,		   		setlayout,      		{.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_t,		   		setlayout,      		{.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,	   		togglefloating, 		{0} },
	{ MODKEY,                       XK_0,		   		view,           		{.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		   		tag,            		{.ui = ~0 } },
	{ MODKEY,                       XK_comma,	   		focusmon,       		{.i = -1 } },
	{ MODKEY,                       XK_period,	   		focusmon,       		{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,	   		tagmon,         		{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	   		tagmon,         		{.i = +1 } },
	{ MODKEY,                       XK_minus,	   		setgaps,        		{.i = -5 } },
	{ MODKEY,                       XK_equal,	   		setgaps,        		{.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,	   		setgaps,        		{.i = 0  } },
	{ MODKEY,                       XK_F5,		   		xrdb,           		{.v = NULL } },
	TAGKEYS(                        XK_1,				   0)
	TAGKEYS(                        XK_2,				   1)
	TAGKEYS(                        XK_3,				   2)
	TAGKEYS(                        XK_4,				   3)
	TAGKEYS(                        XK_5,				   4)
	TAGKEYS(                        XK_6,				   5)
	TAGKEYS(                        XK_7,				   6)
	TAGKEYS(                        XK_8,				   7)
	TAGKEYS(                        XK_9,				   8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "xrdb",           xrdb },
	{ "setlayoutex",    setlayoutex },
};
