#pragma once

enum Keys {
    Arrow_up,
    Arrow_down,
    Arrow_left,
    Arrow_right,
    Space,
    Esc,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9
};

/*
enum Keys get_key(uint8_t bytes[2]) {
    if (bytes[0] == 0xE0) {
        switch (bytes[1]) {
            case 0x48:
                return Arrow_up;
            case 0x50:
                return Arrow_down;
            case 0x4B:
                return Arrow_left;
            case 0x4D:
                return Arrow_right;
            default:
                return Esc;
        }
    } else {
        switch (bytes[0]) {
            case 0x1C:
                return Space;
            case 0x01:
                return Esc;
            default:
                return Esc;
        }
    }
}
*/
