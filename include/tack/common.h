#ifndef TACK_COMMON_H_INCLUDED
#define TACK_COMMON_H_INCLUDED

#include <cstdint>

namespace tack {
enum blend_t : int32_t {
    e_aaaa = 0,
    e_baaa,
    e_abaa,
    e_bbaa,
    e_aaba,
    e_baba,
    e_abba,
    e_bbba,
    e_aaab,
    e_baab,
    e_abab,
    e_bbab,
    e_aabb,
    e_babb,
    e_abbb,
    e_bbbb,
};

enum swizzle_t : int32_t {
    e_xxxx = 0,
    e_yxxx,
    e_zxxx,
    e_wxxx,
    e_xyxx,
    e_yyxx,
    e_zyxx,
    e_wyxx,
    e_xzxx,
    e_yzxx,
    e_zzxx,
    e_wzxx,
    e_xwxx,
    e_ywxx,
    e_zwxx,
    e_wwxx,
    e_xxyx,
    e_yxyx,
    e_zxyx,
    e_wxyx,
    e_xyyx,
    e_yyyx,
    e_zyyx,
    e_wyyx,
    e_xzyx,
    e_yzyx,
    e_zzyx,
    e_wzyx,
    e_xwyx,
    e_ywyx,
    e_zwyx,
    e_wwyx,
    e_xxzx,
    e_yxzx,
    e_zxzx,
    e_wxzx,
    e_xyzx,
    e_yyzx,
    e_zyzx,
    e_wyzx,
    e_xzzx,
    e_yzzx,
    e_zzzx,
    e_wzzx,
    e_xwzx,
    e_ywzx,
    e_zwzx,
    e_wwzx,
    e_xxwx,
    e_yxwx,
    e_zxwx,
    e_wxwx,
    e_xywx,
    e_yywx,
    e_zywx,
    e_wywx,
    e_xzwx,
    e_yzwx,
    e_zzwx,
    e_wzwx,
    e_xwwx,
    e_ywwx,
    e_zwwx,
    e_wwwx,
    e_xxxy,
    e_yxxy,
    e_zxxy,
    e_wxxy,
    e_xyxy,
    e_yyxy,
    e_zyxy,
    e_wyxy,
    e_xzxy,
    e_yzxy,
    e_zzxy,
    e_wzxy,
    e_xwxy,
    e_ywxy,
    e_zwxy,
    e_wwxy,
    e_xxyy,
    e_yxyy,
    e_zxyy,
    e_wxyy,
    e_xyyy,
    e_yyyy,
    e_zyyy,
    e_wyyy,
    e_xzyy,
    e_yzyy,
    e_zzyy,
    e_wzyy,
    e_xwyy,
    e_ywyy,
    e_zwyy,
    e_wwyy,
    e_xxzy,
    e_yxzy,
    e_zxzy,
    e_wxzy,
    e_xyzy,
    e_yyzy,
    e_zyzy,
    e_wyzy,
    e_xzzy,
    e_yzzy,
    e_zzzy,
    e_wzzy,
    e_xwzy,
    e_ywzy,
    e_zwzy,
    e_wwzy,
    e_xxwy,
    e_yxwy,
    e_zxwy,
    e_wxwy,
    e_xywy,
    e_yywy,
    e_zywy,
    e_wywy,
    e_xzwy,
    e_yzwy,
    e_zzwy,
    e_wzwy,
    e_xwwy,
    e_ywwy,
    e_zwwy,
    e_wwwy,
    e_xxxz,
    e_yxxz,
    e_zxxz,
    e_wxxz,
    e_xyxz,
    e_yyxz,
    e_zyxz,
    e_wyxz,
    e_xzxz,
    e_yzxz,
    e_zzxz,
    e_wzxz,
    e_xwxz,
    e_ywxz,
    e_zwxz,
    e_wwxz,
    e_xxyz,
    e_yxyz,
    e_zxyz,
    e_wxyz,
    e_xyyz,
    e_yyyz,
    e_zyyz,
    e_wyyz,
    e_xzyz,
    e_yzyz,
    e_zzyz,
    e_wzyz,
    e_xwyz,
    e_ywyz,
    e_zwyz,
    e_wwyz,
    e_xxzz,
    e_yxzz,
    e_zxzz,
    e_wxzz,
    e_xyzz,
    e_yyzz,
    e_zyzz,
    e_wyzz,
    e_xzzz,
    e_yzzz,
    e_zzzz,
    e_wzzz,
    e_xwzz,
    e_ywzz,
    e_zwzz,
    e_wwzz,
    e_xxwz,
    e_yxwz,
    e_zxwz,
    e_wxwz,
    e_xywz,
    e_yywz,
    e_zywz,
    e_wywz,
    e_xzwz,
    e_yzwz,
    e_zzwz,
    e_wzwz,
    e_xwwz,
    e_ywwz,
    e_zwwz,
    e_wwwz,
    e_xxxw,
    e_yxxw,
    e_zxxw,
    e_wxxw,
    e_xyxw,
    e_yyxw,
    e_zyxw,
    e_wyxw,
    e_xzxw,
    e_yzxw,
    e_zzxw,
    e_wzxw,
    e_xwxw,
    e_ywxw,
    e_zwxw,
    e_wwxw,
    e_xxyw,
    e_yxyw,
    e_zxyw,
    e_wxyw,
    e_xyyw,
    e_yyyw,
    e_zyyw,
    e_wyyw,
    e_xzyw,
    e_yzyw,
    e_zzyw,
    e_wzyw,
    e_xwyw,
    e_ywyw,
    e_zwyw,
    e_wwyw,
    e_xxzw,
    e_yxzw,
    e_zxzw,
    e_wxzw,
    e_xyzw,
    e_yyzw,
    e_zyzw,
    e_wyzw,
    e_xzzw,
    e_yzzw,
    e_zzzw,
    e_wzzw,
    e_xwzw,
    e_ywzw,
    e_zwzw,
    e_wwzw,
    e_xxww,
    e_yxww,
    e_zxww,
    e_wxww,
    e_xyww,
    e_yyww,
    e_zyww,
    e_wyww,
    e_xzww,
    e_yzww,
    e_zzww,
    e_wzww,
    e_xwww,
    e_ywww,
    e_zwww,
    e_wwww,
};
} // tack

#endif // TACK_COMMON_H_INCLUDED