#pragma once

#include <set>

enum ZC_KeyboardKey
{
    ZC_UNKNOWN = 0,

    ZC_RETURN = '\r',
    ZC_ESCAPE = '\x1B',
    ZC_BACKSPACE = '\b',
    ZC_TAB = '\t',
    ZC_SPACE = ' ',
    ZC_EXCLAIM = '!',
    ZC_QUOTEDBL = '"',
    ZC_HASH = '#',
    ZC_PERCENT = '%',
    ZC_DOLLAR = '$',
    ZC_AMPERSAND = '&',
    ZC_QUOTE = '\'',
    ZC_LEFTPAREN = '(',
    ZC_RIGHTPAREN = ')',
    ZC_ASTERISK = '*',
    ZC_PLUS = '+',
    ZC_COMMA = ',',
    ZC_MINUS = '-',
    ZC_PERIOD = '.',
    ZC_SLASH = '/',
    ZC_0 = '0',
    ZC_1 = '1',
    ZC_2 = '2',
    ZC_3 = '3',
    ZC_4 = '4',
    ZC_5 = '5',
    ZC_6 = '6',
    ZC_7 = '7',
    ZC_8 = '8',
    ZC_9 = '9',
    ZC_COLON = ':',
    ZC_SEMICOLON = ';',
    ZC_LESS = '<',
    ZC_EQUALS = '=',
    ZC_GREATER = '>',
    ZC_QUESTION = '?',
    ZC_AT = '@',

    /*
       Skip uppercase letters
     */

    ZC_LEFTBRACKET = '[',
    ZC_BACKSLASH = '\\',
    ZC_RIGHTBRACKET = ']',
    ZC_CARET = '^',
    ZC_UNDERSCORE = '_',
    ZC_BACKQUOTE = '`',
    ZC_a = 'a',
    ZC_b = 'b',
    ZC_c = 'c',
    ZC_d = 'd',
    ZC_e = 'e',
    ZC_f = 'f',
    ZC_g = 'g',
    ZC_h = 'h',
    ZC_i = 'i',
    ZC_j = 'j',
    ZC_k = 'k',
    ZC_l = 'l',
    ZC_m = 'm',
    ZC_n = 'n',
    ZC_o = 'o',
    ZC_p = 'p',
    ZC_q = 'q',
    ZC_r = 'r',
    ZC_s = 's',
    ZC_t = 't',
    ZC_u = 'u',
    ZC_v = 'v',
    ZC_w = 'w',
    ZC_x = 'x',
    ZC_y = 'y',
    ZC_z = 'z'
};

struct ZC_Button
{
    enum State
    {
        Pressed,
        Unpressed
    };

    Key key;
    State state;
};

struct ZC_ActiveButtons
{
    ZC_ActiveButtons() noexcept;

    std::set<ZC_Button> buttons;
};

ZC_ActiveButtons::ZC_ActiveButtons() noexcept
{

}

class ZC_Keyboard
{
public:
    ZC_Keyboard() = delete;
    
    void Assume

private:

};