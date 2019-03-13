#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "report.h"

Menu* Menu_New(char* title)
{
    Menu* m = (Menu*)malloc(sizeof(Menu));
    if (m)
    {
        if (title)
        {
            int len = strlen(title);
            m->title = (char*)malloc(sizeof(char) * (len + 1));
            m->width = len + 4;
            if (m->title)
                strcpy(m->title, title);
        }
        else
        {
            m->title = NULL;
            m->width = 4;
        }
        m->options = NULL;
        m->options_count = m->selected_option = m->click = 0;
    }
    return m;
}

void Menu_Delete(Menu* m)
{
    if (!m)
        return;

    struct MenuOption* it = m->options;
    struct MenuOption* erase;

    while (it)
    {
        erase = it;
        it = it->next;

        if (erase->option)
            free(erase->option);

        free(erase);
    }

    if (m->title)
        free(m->title);

    free(m);
}

void Menu_AddOption(Menu* m, char* option)
{
    if (!m)
        return;

    struct MenuOption* opt = (struct MenuOption*)malloc(sizeof(struct MenuOption));
    if (opt)
    {
        opt->option = (char*)malloc(sizeof(char) * (strlen(option) + 1));

        if (opt->option)
        {
            strcpy(opt->option, option);
            if (m->width < strlen(opt->option) + 4)
                m->width = strlen(opt->option) + 4;
        }

        opt->next = m->options;
        m->options = opt;
        m->options_count++;

        if (m->selected_option == 0)
            m->selected_option = 1;
    }
}

void Menu_Draw(Menu* m, Display* d, int row, int col)
{
    if (!m || !d)
        return;

    struct MenuOption* opt = m->options;
    int i = m->options_count;
    char buffer[40];
    while (opt)
    {
        if (opt->option)
        {
            if (i == m->selected_option)
            {
                sprintf(buffer, "> %s <", opt->option);
                if (has_colors())
                    Display_SetColor(d, COLOR_RED, COLOR_WHITE);
                else
                    Display_SetAttributes(d, A_REVERSE);
            }
            else
                sprintf(buffer, "%s", opt->option);

            Display_DrawText(d, buffer,
                             row + i - m->options_count/2 + (m->title != NULL),
                             col + 1, 1);
        }
        opt = opt->next;
        i--;
        Display_SetColor(d, -1, -1);
        Display_SetAttributes(d, 0);
    }
    if (m->title)
    {
        Display_SetAttributes(d, A_BOLD);
        Display_DrawText(d, m->title, row - m->options_count / 2, col + 1, 1);
        Display_SetAttributes(d, 0);
        Display_DrawBox(d, row - m->options_count / 2 - 2,
                        col - m->width / 2 - 1, m->width + 3, m->options_count + 5);
    }
    else
        Display_DrawBox(d, row - m->options_count / 2 - 1,
                        col - m->width / 2 - 1, m->width + 3, m->options_count + 3);

}

void Menu_Input(Menu* m, int key)
{
    if (!m)
        return;

    switch (key)
    {
    case KEY_UP:
    case 450:
        if (m->selected_option > 1)
            m->selected_option--;
        break;
    case KEY_DOWN:
    case 456:
        if (m->selected_option < m->options_count)
            m->selected_option++;
        break;
    case KEY_ENTER:
    case 10:
    case 13:
        m->click = m->selected_option;
    default:
        break;
    }
}

int Menu_Click(Menu* m)
{
    int ret = m->click;
    m->click = 0;
    return ret;
}
