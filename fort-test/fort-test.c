#include "fort-test.h"
#include "submodules/log.h/log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

//////////////////////////////////////////////


TEST t_fort_beautiful(void){
  ft_table_t *table = ft_create_table();

  ft_set_border_style(table, FT_NICE_STYLE);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

  /* Filling table with data */
  ft_u8write_ln(table, "Тест", "Итерации", "ms/op", "Тики", "Результат");
  ft_u8write_ln(table, "n-body", "1000", "1.6", "1,500,000", "✔");
  ft_add_separator(table);
  ft_u8write_ln(table, "regex-redux", "1000", "0.8", "8,000,000");
  ft_u8write_ln(table, "", "2500", "3.9", "27,000,000", "✖");
  ft_u8write_ln(table, "", "10000", "12.5", "96,800,000");
  ft_add_separator(table);
  ft_u8write_ln(table, "mandelbrot", "1000", "8.1", "89,000,000");
  ft_u8write_ln(table, "", "2500", "19.8", "320,000,000", "✔");
  ft_u8write_ln(table, "", "10000", "60.7", "987,000,000");
  ft_add_separator(table);
  ft_set_cell_span(table, 8, 0, 4);
  ft_u8write_ln(table, "Итог", "", "", "", "✖");

  /* Setting text styles */
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, 8, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, FT_ANY_ROW, 0, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_BOLD);
  ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_COLUMN, FT_CPROP_CONT_TEXT_STYLE, FT_TSTYLE_ITALIC);

  /* Set alignment */
  ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
  ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
  ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
  ft_set_cell_prop(table, FT_ANY_ROW, 4, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_prop(table, 8, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);

  /* Set colors */
  ft_set_cell_prop(table, 1, 4, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_set_cell_prop(table, 3, 4, FT_CPROP_CONT_FG_COLOR, FT_COLOR_RED);
  ft_set_cell_prop(table, 6, 4, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);
  ft_set_cell_prop(table, 8, 4, FT_CPROP_CONT_FG_COLOR, FT_COLOR_RED);
  ft_set_cell_prop(table, 3, 2, FT_CPROP_CONT_FG_COLOR, FT_COLOR_RED);
  ft_set_cell_prop(table, 4, 3, FT_CPROP_CONT_BG_COLOR, FT_COLOR_LIGHT_RED);
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_BLUE);

  /* Move table to the center of the screen */
  ft_set_tbl_prop(table, FT_TPROP_TOP_MARGIN, 1);
  ft_set_tbl_prop(table, FT_TPROP_LEFT_MARGIN, 10);

  const char *table_str = ft_to_u8string(table);

  printf("\nTable:\n%s\n\n ", table_str);
  ft_destroy_table(table);
  PASS();
} /* t_fort_beautiful */


TEST t_fort1(void){
  ft_table_t *table = ft_create_table();

  /* Setup header */
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, "N", "Driver", "Time", "Avg Speed");

  /* Fill table */
  ft_write_ln(table, "1", "Ricciardo", "1:25.945", "222.128");
  ft_write_ln(table, "2", "Hamilton", "1:26.373", "221.027");
  ft_add_separator(table);
  ft_write_ln(table, "3", "Verstappen", "1:26.469", "220.782");

  /* Set custom border style */
  struct ft_border_chars border;

  border.top_border_ch    = "^";
  border.separator_ch     = "=";
  border.bottom_border_ch = "v";
  border.side_border_ch   = "|";
  border.out_intersect_ch = "x";
  border.in_intersect_ch  = "x";

  struct ft_border_style border_style;

  memcpy(&border_style.border_chs, &border, sizeof(struct ft_border_chars));
  memcpy(&border_style.header_border_chs, &border, sizeof(struct ft_border_chars));
  border_style.hor_separator_char = "~";
  ft_set_border_style(table, &border_style);

  printf("\n%s\n", ft_to_string(table));
  ft_destroy_table(table);
  PASS();
}


TEST t_fort3(void){
  ft_table_t *table = ft_create_table();

  /* Change border style */
  ft_set_border_style(table, FT_DOUBLE2_STYLE);

  /* Setup header */
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, "Sed", "Aenean", "Text");

  /* Fill table */
  ft_write_ln(table, "Duis", "Aliquam",
              "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n"
              "In accumsan felis eros, nec malesuada sapien bibendum eget.");
  ft_write_ln(table, "Mauris", "Curabitur",
              "Proin condimentum eros viverra nunc ultricies, at fringilla \n"
              "quam pellentesque.");
  ft_write_ln(table, "Summary", "", "Sed tempor est eget odio varius dignissim.");

  /* Setup alignments and cell span */
  ft_set_cell_prop(table, 0, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_prop(table, 3, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
  ft_set_cell_span(table, 3, 0, 2);

  printf("\n%s\n", ft_to_string(table));
  ft_destroy_table(table);
  PASS();
}


TEST t_fort4(void){
  ft_table_t *table = ft_create_table();

  ft_set_border_style(table, FT_DOUBLE2_STYLE);

  /* 2 last columns are aligned right */
  ft_set_cell_prop(table, FT_ANY_ROW, 2, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);
  ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_RIGHT);

  /* Setup header */
  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_u8write_ln(table, "Figure", "Formula", "Volume, cm³", "Accuracy");

  ft_u8write_ln(table, "Sphere ○", "4πR³/3", "3.145", "±0.3");
  ft_u8write_ln(table, "Cone ◸", "πR²h/3", "4.95", "±0.25");
  ft_u8write_ln(table, "Random", "∫ρdv", "12.95", "±0.75");

  printf("\n%s\n", (const char *)ft_to_u8string(table));
  ft_destroy_table(table);
  PASS();
}


TEST t_fort2(void){
  ft_table_t *table = ft_create_table();

  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  const char *ctab[4][3] = {
    { "N", "Planet",  "Speed, km/s" },
    { "1", "Mercury", "47.362"      },
    { "2", "Venus",   "35.02"       },
    { "3", "Earth",   "29.78"       }
  };

  ft_table_write_ln(table, 4, 3, (const char **)ctab);

  printf("\n%s\n", ft_to_string(table));
  ft_destroy_table(table);
  PASS();
}


TEST t_fort(void){
  ft_table_t *table = ft_create_table();

  ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
  ft_write_ln(table, "N", "Driver", "Time", "Avg Speed");

  ft_write_ln(table, "1", "Ricciardo", "1:25.945", "222.128");
  ft_write_ln(table, "2", "Hamilton", "1:26.373", "221.027");
  ft_write_ln(table, "3", "Verstappen", "1:26.469", "220.782");

  printf("\n%s\n", ft_to_string(table));
  ft_destroy_table(table);
  PASS();
}

GREATEST_MAIN_DEFS();

SUITE(s_fort){
  RUN_TEST(t_fort);
  RUN_TEST(t_fort_beautiful);
  RUN_TEST(t_fort1);
  RUN_TEST(t_fort2);
  RUN_TEST(t_fort3);
  RUN_TEST(t_fort4);
  PASS();
}


int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  (void)argc; (void)argv;
  RUN_SUITE(s_fort);

  GREATEST_MAIN_END();
  return(0);
}

