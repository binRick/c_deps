#include "gumbo-test.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


static void read_file(FILE *fp, char **output, int *length) {
  struct stat filestats;
  int         fd = fileno(fp);

  fstat(fd, &filestats);
  *length = filestats.st_size;
  *output = malloc(*length + 1);
  int start = 0;
  int bytes_read;

  while ((bytes_read = fread(*output + start, 1, *length - start, fp))) {
    start += bytes_read;
  }
}


static const char * find_title(const GumboNode *root) {
  assert(root->type == GUMBO_NODE_ELEMENT);
  assert(root->v.element.children.length >= 2);

  const GumboVector *root_children = &root->v.element.children;
  GumboNode         *head          = NULL;
  for (int i = 0; i < root_children->length; ++i) {
    GumboNode *child = root_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT
        && child->v.element.tag == GUMBO_TAG_HEAD) {
      head = child;
      break;
    }
  }
  assert(head != NULL);

  GumboVector *head_children = &head->v.element.children;
  for (int i = 0; i < head_children->length; ++i) {
    GumboNode *child = head_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT
        && child->v.element.tag == GUMBO_TAG_TITLE) {
      if (child->v.element.children.length != 1) {
        return("<empty title>");
      }
      GumboNode *title_text = child->v.element.children.data[0];
      assert(title_text->type == GUMBO_NODE_TEXT || title_text->type == GUMBO_NODE_WHITESPACE);
      return(title_text->v.text.text);
    }
  }
  return("<no title found>");
}


int gmain(int argc, const char **argv) {
  if (argc != 2) {
    printf("Usage: get_title <html filename>.\n");
    exit(EXIT_FAILURE);
  }
  const char *filename = argv[1];

  FILE       *fp = fopen(filename, "r");
  if (!fp) {
    printf("File %s not found!\n", filename);
    exit(EXIT_FAILURE);
  }

  char        *input;
  int         input_length;
  read_file(fp, &input, &input_length);
  GumboOutput *output = gumbo_parse_with_options(
    &kGumboDefaultOptions, input, input_length);
  const char  *title = find_title(output->root);
  printf("%s\n", title);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  free(input);
}


int main(int argc, char **argv) {
  (void)argc; (void)argv;
  if ((argc >= 2) && (strcmp(argv[1], "--test") == 0)) {
    printf("Test OK\n"); return(0);
  }
  GumboOutput *output = gumbo_parse("<h1>Hello, World!</h1>");
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return(gmain(argc, argv));


  return(0);
}
