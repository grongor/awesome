/*
 * window.h - window object header
 *
 * Copyright © 2009 Julien Danjou <julien@danjou.info>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AWESOME_OBJECTS_WINDOW_H
#define AWESOME_OBJECTS_WINDOW_H

#include <xcb/xcb_icccm.h>

#include "area.h"
#include "common/luaobject.h"

#define WINDOW_OBJECT_HEADER \
    LUA_OBJECT_HEADER \
    /** The X window number */ \
    xcb_window_t window; \
    /** The frame window, might be XCB_NONE */ \
    xcb_window_t frame_window; \
    /** The window pixmap */ \
    xcb_window_t pixmap; \
    /** Cursor */ \
    char *cursor; \
    /** True if the window is banned from the view */ \
    bool banned; \
    /** True if the window is visible */ \
    bool visible; \
    /** True if the window can have focus */ \
    bool focusable; \
    /** True if the window is resizable and/or movable. */ \
    bool movable, resizable; \
    /** Parent window */ \
    window_t *parent; \
    /** Window geometry */ \
    area_t geometry; \
    /** Size hints */ \
    xcb_size_hints_t size_hints; \
    /** Windows layer */ \
    int8_t layer; \
    /** Window childrens stack */ \
    window_array_t childrens; \

typedef struct window_t window_t;
DO_ARRAY(window_t *, window, DO_NOTHING)
/** Window structure */
struct window_t
{
    WINDOW_OBJECT_HEADER
};

typedef bool (*lua_interface_window_isvisible_t)(window_t *);

typedef struct
{
    LUA_CLASS_HEADER
    /** The function to call to know if a window is visible */
    lua_interface_window_isvisible_t isvisible;
} lua_interface_window_t;

static inline int
window_cmp(const void *a, const void *b)
{
    window_t *x = *((window_t **) a), *y = *((window_t**) b);
    return x->window > y->window ? 1 : (x->window < y->window ? -1 : 0);
}

#include "common/luaobject.h"

lua_class_t window_class;
LUA_OBJECT_SIGNAL_FUNCS(window, window_t)

void window_class_setup(lua_State *);

void window_ban(window_t *);
void window_ban_unfocus(window_t *);
void window_unban(window_t *);
void window_focus_update(window_t *);
void window_unfocus_update(window_t *);
void window_focus(lua_State *, int);
area_t window_geometry_hints(window_t *, area_t);

void window_set_opacity(lua_State *, window_t *, double);
void window_set_border_width(lua_State *, window_t *, int);
void window_set_sticky(lua_State *, window_t *, bool);
bool window_set_geometry(lua_State *, window_t *, area_t);

bool window_isvisible(lua_State *, int);

int luaA_window_get_focusable(lua_State *, window_t *);
int luaA_window_set_focusable(lua_State *, window_t *);
int luaA_window_get_parent(lua_State *, window_t *);

#endif
// vim: filetype=c:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=80
