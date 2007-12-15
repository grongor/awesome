#include "util.h"
#include "widget.h"

static char name[] = "focustitle";

static int
focustitle_draw(DrawCtx *ctx,
                awesome_config *awesomeconf __attribute__ ((unused)),
                VirtScreen vscreen,
                int screen __attribute__ ((unused)),
                int offset, 
                int used,
                int align)
{
    Client *sel = awesomeconf->focus->client;
    int location = calculate_offset(vscreen.statusbar.width, 0, offset, align);

    if(sel)
    {
        drawtext(ctx, location, 0, vscreen.statusbar.width - used,
                 vscreen.statusbar.height, vscreen.font, sel->name,
                 vscreen.colors_selected);
        if(sel->isfloating)
            drawcircle(ctx, location, 0,
                       (vscreen.font->height + 2) / 4,
                       sel->ismax,
                       vscreen.colors_selected[ColFG]);
    }
    else
        drawtext(ctx, location, 0, vscreen.statusbar.width - used,
                 vscreen.statusbar.height, vscreen.font, NULL,
                 vscreen.colors_normal);
    return vscreen.statusbar.width - used;
}

Widget *
focustitle_new(Statusbar *statusbar)
{
    Widget *w;
    w = p_new(Widget, 1);
    w->draw = focustitle_draw;
    w->statusbar = statusbar;
    w->name = name;
    w->alignment = AlignFlex;
    return w;
}

// vim: filetype=c:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99
