/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Theme engine for labwc
 *
 * Copyright Johan Malm 2020-2021
 */

#ifndef LABWC_THEME_H
#define LABWC_THEME_H

#include <stdio.h>
#include <wlr/render/wlr_renderer.h>

enum lab_justification {
	LAB_JUSTIFY_LEFT,
	LAB_JUSTIFY_CENTER,
	LAB_JUSTIFY_RIGHT,
};

enum lab_corner {
	LAB_CORNER_UNKNOWN = 0,
	LAB_CORNER_TOP_LEFT,
	LAB_CORNER_TOP_RIGHT,
};

struct theme {
	int border_width;
	int padding_height;
	int title_height;
	int menu_overlap_x;
	int menu_overlap_y;

	/* colors */
	float window_active_border_color[4];
	float window_inactive_border_color[4];

	float window_toggled_keybinds_color[4];

	float window_active_title_bg_color[4];
	float window_inactive_title_bg_color[4];

	float window_active_label_text_color[4];
	float window_inactive_label_text_color[4];
	enum lab_justification window_label_text_justify;

	/* button colors */
	float window_active_button_menu_unpressed_image_color[4];
	float window_active_button_iconify_unpressed_image_color[4];
	float window_active_button_max_unpressed_image_color[4];
	float window_active_button_close_unpressed_image_color[4];
	float window_inactive_button_menu_unpressed_image_color[4];
	float window_inactive_button_iconify_unpressed_image_color[4];
	float window_inactive_button_max_unpressed_image_color[4];
	float window_inactive_button_close_unpressed_image_color[4];
	/* TODO: add pressed and hover colors for buttons */

	int menu_item_padding_x;
	int menu_item_padding_y;

	float menu_items_bg_color[4];
	float menu_items_text_color[4];
	float menu_items_active_bg_color[4];
	float menu_items_active_text_color[4];

	int menu_min_width;
	int menu_max_width;

	int menu_separator_line_thickness;
	int menu_separator_padding_width;
	int menu_separator_padding_height;
	float menu_separator_color[4];

	int osd_border_width;

	float osd_bg_color[4];
	float osd_border_color[4];
	float osd_label_text_color[4];

	int osd_window_switcher_width;
	int osd_window_switcher_padding;
	int osd_window_switcher_item_padding_x;
	int osd_window_switcher_item_padding_y;
	int osd_window_switcher_item_active_border_width;

	/* textures */
	struct lab_data_buffer *button_close_active_unpressed;
	struct lab_data_buffer *button_maximize_active_unpressed;
	struct lab_data_buffer *button_iconify_active_unpressed;
	struct lab_data_buffer *button_menu_active_unpressed;

	struct lab_data_buffer *button_close_inactive_unpressed;
	struct lab_data_buffer *button_maximize_inactive_unpressed;
	struct lab_data_buffer *button_iconify_inactive_unpressed;
	struct lab_data_buffer *button_menu_inactive_unpressed;

	struct lab_data_buffer *corner_top_left_active_normal;
	struct lab_data_buffer *corner_top_right_active_normal;
	struct lab_data_buffer *corner_top_left_inactive_normal;
	struct lab_data_buffer *corner_top_right_inactive_normal;

	/* not set in rc.xml/themerc, but derived from font & padding_height */
	int osd_window_switcher_item_height;
};

/**
 * theme_init - read openbox theme and generate button textures
 * @theme: theme data
 * @theme_name: theme-name in <theme-dir>/<theme-name>/openbox-3/themerc
 * Note <theme-dir> is obtained in theme-dir.c
 */
void theme_init(struct theme *theme, const char *theme_name);

/**
 * theme_finish - free button textures
 * @theme: theme data
 */
void theme_finish(struct theme *theme);

/**
 * theme_create_custom_corner - create corners - rounded or not - using custom color
 * @theme: theme data
 * @lab_corner: corner enum value, top left or top right
 * @bg_color: pointer to color array
 */
struct lab_data_buffer * theme_create_custom_corner(struct theme *theme, enum lab_corner corner, float *bg_color);

/**
 * theme_customize_with_border_color - fill in the given theme color fields by custom color
 * @theme: theme data
 * @color: pointer to color array
 */
void theme_customize_with_border_color(struct theme *theme, float *color);

void parse_hexstr(const char *hex, float *rgba);

#endif /* LABWC_THEME_H */
