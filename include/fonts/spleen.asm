
; spleen font declaration
; This standard allows c to extern this and reinterpret this as a c-defined struct

init_spleen_font:
	mov byte [spleen_font], 5
	mov byte [spleen_font + 1], 8
	lea eax, __spleen_char_32
	mov byte [spleen_font_data + 32], eax
	lea eax, __spleen_char_33
	mov [spleen_font_data + 33], eax
	lea eax, __spleen_char_34
	mov [spleen_font_data + 34], eax
	lea eax, __spleen_char_35
	mov [spleen_font_data + 35], eax
	lea eax, __spleen_char_36
	mov [spleen_font_data + 36], eax
	lea eax, __spleen_char_37
	mov [spleen_font_data + 37], eax
	lea eax, __spleen_char_38
	mov [spleen_font_data + 38], eax
	lea eax, __spleen_char_39
	mov [spleen_font_data + 39], eax
	lea eax, __spleen_char_40
	mov [spleen_font_data + 40], eax
	lea eax, __spleen_char_41
	mov [spleen_font_data + 41], eax
	lea eax, __spleen_char_42
	mov [spleen_font_data + 42], eax
	lea eax, __spleen_char_43
	mov [spleen_font_data + 43], eax
	lea eax, __spleen_char_44
	mov [spleen_font_data + 44], eax
	lea eax, __spleen_char_45
	mov [spleen_font_data + 45], eax
	lea eax, __spleen_char_46
	mov [spleen_font_data + 46], eax
	lea eax, __spleen_char_47
	mov [spleen_font_data + 47], eax
	lea eax, __spleen_char_48
	mov [spleen_font_data + 48], eax
	lea eax, __spleen_char_49
	mov [spleen_font_data + 49], eax
	lea eax, __spleen_char_50
	mov [spleen_font_data + 50], eax
	lea eax, __spleen_char_51
	mov [spleen_font_data + 51], eax
	lea eax, __spleen_char_52
	mov [spleen_font_data + 52], eax
	lea eax, __spleen_char_53
	mov [spleen_font_data + 53], eax
	lea eax, __spleen_char_54
	mov [spleen_font_data + 54], eax
	lea eax, __spleen_char_55
	mov [spleen_font_data + 55], eax
	lea eax, __spleen_char_56
	mov [spleen_font_data + 56], eax
	lea eax, __spleen_char_57
	mov [spleen_font_data + 57], eax
	lea eax, __spleen_char_58
	mov [spleen_font_data + 58], eax
	lea eax, __spleen_char_59
	mov [spleen_font_data + 59], eax
	lea eax, __spleen_char_60
	mov [spleen_font_data + 60], eax
	lea eax, __spleen_char_61
	mov [spleen_font_data + 61], eax
	lea eax, __spleen_char_62
	mov [spleen_font_data + 62], eax
	lea eax, __spleen_char_63
	mov [spleen_font_data + 63], eax
	lea eax, __spleen_char_64
	mov [spleen_font_data + 64], eax
	lea eax, __spleen_char_65
	mov [spleen_font_data + 65], eax
	lea eax, __spleen_char_66
	mov [spleen_font_data + 66], eax
	lea eax, __spleen_char_67
	mov [spleen_font_data + 67], eax
	lea eax, __spleen_char_68
	mov [spleen_font_data + 68], eax
	lea eax, __spleen_char_69
	mov [spleen_font_data + 69], eax
	lea eax, __spleen_char_70
	mov [spleen_font_data + 70], eax
	lea eax, __spleen_char_71
	mov [spleen_font_data + 71], eax
	lea eax, __spleen_char_72
	mov [spleen_font_data + 72], eax
	lea eax, __spleen_char_73
	mov [spleen_font_data + 73], eax
	lea eax, __spleen_char_74
	mov [spleen_font_data + 74], eax
	lea eax, __spleen_char_75
	mov [spleen_font_data + 75], eax
	lea eax, __spleen_char_76
	mov [spleen_font_data + 76], eax
	lea eax, __spleen_char_77
	mov [spleen_font_data + 77], eax
	lea eax, __spleen_char_78
	mov [spleen_font_data + 78], eax
	lea eax, __spleen_char_79
	mov [spleen_font_data + 79], eax
	lea eax, __spleen_char_80
	mov [spleen_font_data + 80], eax
	lea eax, __spleen_char_81
	mov [spleen_font_data + 81], eax
	lea eax, __spleen_char_82
	mov [spleen_font_data + 82], eax
	lea eax, __spleen_char_83
	mov [spleen_font_data + 83], eax
	lea eax, __spleen_char_84
	mov [spleen_font_data + 84], eax
	lea eax, __spleen_char_85
	mov [spleen_font_data + 85], eax
	lea eax, __spleen_char_86
	mov [spleen_font_data + 86], eax
	lea eax, __spleen_char_87
	mov [spleen_font_data + 87], eax
	lea eax, __spleen_char_88
	mov [spleen_font_data + 88], eax
	lea eax, __spleen_char_89
	mov [spleen_font_data + 89], eax
	lea eax, __spleen_char_90
	mov [spleen_font_data + 90], eax
	lea eax, __spleen_char_91
	mov [spleen_font_data + 91], eax
	lea eax, __spleen_char_92
	mov [spleen_font_data + 92], eax
	lea eax, __spleen_char_93
	mov [spleen_font_data + 93], eax
	lea eax, __spleen_char_94
	mov [spleen_font_data + 94], eax
	lea eax, __spleen_char_95
	mov [spleen_font_data + 95], eax
	lea eax, __spleen_char_96
	mov [spleen_font_data + 96], eax
	lea eax, __spleen_char_97
	mov [spleen_font_data + 97], eax
	lea eax, __spleen_char_98
	mov [spleen_font_data + 98], eax
	lea eax, __spleen_char_99
	mov [spleen_font_data + 99], eax
	lea eax, __spleen_char_100
	mov [spleen_font_data + 100], eax
	lea eax, __spleen_char_101
	mov [spleen_font_data + 101], eax
	lea eax, __spleen_char_102
	mov [spleen_font_data + 102], eax
	lea eax, __spleen_char_103
	mov [spleen_font_data + 103], eax
	lea eax, __spleen_char_104
	mov [spleen_font_data + 104], eax
	lea eax, __spleen_char_105
	mov [spleen_font_data + 105], eax
	lea eax, __spleen_char_106
	mov [spleen_font_data + 106], eax
	lea eax, __spleen_char_107
	mov [spleen_font_data + 107], eax
	lea eax, __spleen_char_108
	mov [spleen_font_data + 108], eax
	lea eax, __spleen_char_109
	mov [spleen_font_data + 109], eax
	lea eax, __spleen_char_110
	mov [spleen_font_data + 110], eax
	lea eax, __spleen_char_111
	mov [spleen_font_data + 111], eax
	lea eax, __spleen_char_112
	mov [spleen_font_data + 112], eax
	lea eax, __spleen_char_113
	mov [spleen_font_data + 113], eax
	lea eax, __spleen_char_114
	mov [spleen_font_data + 114], eax
	lea eax, __spleen_char_115
	mov [spleen_font_data + 115], eax
	lea eax, __spleen_char_116
	mov [spleen_font_data + 116], eax
	lea eax, __spleen_char_117
	mov [spleen_font_data + 117], eax
	lea eax, __spleen_char_118
	mov [spleen_font_data + 118], eax
	lea eax, __spleen_char_119
	mov [spleen_font_data + 119], eax
	lea eax, __spleen_char_120
	mov [spleen_font_data + 120], eax
	lea eax, __spleen_char_121
	mov [spleen_font_data + 121], eax
	lea eax, __spleen_char_122
	mov [spleen_font_data + 122], eax
	lea eax, __spleen_char_123
	mov [spleen_font_data + 123], eax
	lea eax, __spleen_char_124
	mov [spleen_font_data + 124], eax
	lea eax, __spleen_char_125
	mov [spleen_font_data + 125], eax
	lea eax, __spleen_char_126
	mov [spleen_font_data + 126], eax

spleen_font:
	db 0, 0 ; width and height
	spleen_font_data: times 128 db 0 ; pointer array

__spleen_char_32:
	db 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
__spleen_char_33:
	db 0x20, 0x20, 0x20, 0x20, 0x20, 0x0, 0x20, 0x0
__spleen_char_34:
	db 0x50, 0x50, 0x50, 0x0, 0x0, 0x0, 0x0, 0x0
__spleen_char_35:
	db 0x0, 0x50, 0xF8, 0x50, 0x50, 0xF8, 0x50, 0x0
__spleen_char_36:
	db 0x20, 0x70, 0xA0, 0x60, 0x30, 0x30, 0xE0, 0x20
__spleen_char_37:
	db 0x10, 0x90, 0xA0, 0x20, 0x40, 0x50, 0x90, 0x80
__spleen_char_38:
	db 0x20, 0x50, 0x50, 0x60, 0xA8, 0x90, 0x68, 0x0
__spleen_char_39:
	db 0x20, 0x20, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0
__spleen_char_40:
	db 0x10, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x10
__spleen_char_41:
	db 0x40, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0x40
__spleen_char_42:
	db 0x0, 0x0, 0x90, 0x60, 0xF0, 0x60, 0x90, 0x0
__spleen_char_43:
	db 0x0, 0x0, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x0
__spleen_char_44:
	db 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x20, 0x40
__spleen_char_45:
	db 0x0, 0x0, 0x0, 0x0, 0xF0, 0x0, 0x0, 0x0
__spleen_char_46:
	db 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x20, 0x0
__spleen_char_47:
	db 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80
__spleen_char_48:
	db 0x0, 0x60, 0x90, 0xB0, 0xD0, 0x90, 0x60, 0x0
__spleen_char_49:
	db 0x0, 0x20, 0x60, 0x20, 0x20, 0x20, 0x70, 0x0
__spleen_char_50:
	db 0x0, 0x60, 0x90, 0x10, 0x60, 0x80, 0xF0, 0x0
__spleen_char_51:
	db 0x0, 0x60, 0x90, 0x20, 0x10, 0x90, 0x60, 0x0
__spleen_char_52:
	db 0x0, 0x80, 0xA0, 0xA0, 0xF0, 0x20, 0x20, 0x0
__spleen_char_53:
	db 0x0, 0xF0, 0x80, 0xE0, 0x10, 0x10, 0xE0, 0x0
__spleen_char_54:
	db 0x0, 0x60, 0x80, 0xE0, 0x90, 0x90, 0x60, 0x0
__spleen_char_55:
	db 0x0, 0xF0, 0x90, 0x10, 0x20, 0x40, 0x40, 0x0
__spleen_char_56:
	db 0x0, 0x60, 0x90, 0x60, 0x90, 0x90, 0x60, 0x0
__spleen_char_57:
	db 0x0, 0x60, 0x90, 0x90, 0x70, 0x10, 0x60, 0x0
__spleen_char_58:
	db 0x0, 0x0, 0x0, 0x20, 0x0, 0x0, 0x20, 0x0
__spleen_char_59:
	db 0x0, 0x0, 0x0, 0x20, 0x0, 0x20, 0x20, 0x40
__spleen_char_60:
	db 0x0, 0x10, 0x20, 0x40, 0x40, 0x20, 0x10, 0x0
__spleen_char_61:
	db 0x0, 0x0, 0x0, 0xF0, 0x0, 0xF0, 0x0, 0x0
__spleen_char_62:
	db 0x0, 0x40, 0x20, 0x10, 0x10, 0x20, 0x40, 0x0
__spleen_char_63:
	db 0x60, 0x90, 0x10, 0x20, 0x40, 0x0, 0x40, 0x0
__spleen_char_64:
	db 0x0, 0x60, 0x90, 0xB0, 0xB0, 0x80, 0x70, 0x0
__spleen_char_65:
	db 0x0, 0x60, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x0
__spleen_char_66:
	db 0x0, 0xE0, 0x90, 0xE0, 0x90, 0x90, 0xE0, 0x0
__spleen_char_67:
	db 0x0, 0x70, 0x80, 0x80, 0x80, 0x80, 0x70, 0x0
__spleen_char_68:
	db 0x0, 0xE0, 0x90, 0x90, 0x90, 0x90, 0xE0, 0x0
__spleen_char_69:
	db 0x0, 0x70, 0x80, 0xE0, 0x80, 0x80, 0x70, 0x0
__spleen_char_70:
	db 0x0, 0x70, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x0
__spleen_char_71:
	db 0x0, 0x70, 0x80, 0xB0, 0x90, 0x90, 0x70, 0x0
__spleen_char_72:
	db 0x0, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x90, 0x0
__spleen_char_73:
	db 0x0, 0x70, 0x20, 0x20, 0x20, 0x20, 0x70, 0x0
__spleen_char_74:
	db 0x0, 0x70, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x0
__spleen_char_75:
	db 0x0, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x90, 0x0
__spleen_char_76:
	db 0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x70, 0x0
__spleen_char_77:
	db 0x0, 0x90, 0xF0, 0xF0, 0x90, 0x90, 0x90, 0x0
__spleen_char_78:
	db 0x0, 0x90, 0xD0, 0xD0, 0xB0, 0xB0, 0x90, 0x0
__spleen_char_79:
	db 0x0, 0x60, 0x90, 0x90, 0x90, 0x90, 0x60, 0x0
__spleen_char_80:
	db 0x0, 0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80, 0x0
__spleen_char_81:
	db 0x0, 0x60, 0x90, 0x90, 0x90, 0x90, 0x60, 0x30
__spleen_char_82:
	db 0x0, 0xE0, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x0
__spleen_char_83:
	db 0x0, 0x70, 0x80, 0x60, 0x10, 0x10, 0xE0, 0x0
__spleen_char_84:
	db 0x0, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0
__spleen_char_85:
	db 0x0, 0x90, 0x90, 0x90, 0x90, 0x90, 0x70, 0x0
__spleen_char_86:
	db 0x0, 0x90, 0x90, 0x90, 0x90, 0x60, 0x60, 0x0
__spleen_char_87:
	db 0x0, 0x90, 0x90, 0x90, 0xF0, 0xF0, 0x90, 0x0
__spleen_char_88:
	db 0x0, 0x90, 0x90, 0x60, 0x60, 0x90, 0x90, 0x0
__spleen_char_89:
	db 0x0, 0x90, 0x90, 0x90, 0x70, 0x10, 0xE0, 0x0
__spleen_char_90:
	db 0x0, 0xF0, 0x10, 0x20, 0x40, 0x80, 0xF0, 0x0
__spleen_char_91:
	db 0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70
__spleen_char_92:
	db 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10
__spleen_char_93:
	db 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70
__spleen_char_94:
	db 0x0, 0x20, 0x50, 0x88, 0x0, 0x0, 0x0, 0x0
__spleen_char_95:
	db 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xF0
__spleen_char_96:
	db 0x40, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
__spleen_char_97:
	db 0x0, 0x0, 0x60, 0x10, 0x70, 0x90, 0x70, 0x0
__spleen_char_98:
	db 0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0x0
__spleen_char_99:
	db 0x0, 0x0, 0x70, 0x80, 0x80, 0x80, 0x70, 0x0
__spleen_char_100:
	db 0x10, 0x10, 0x70, 0x90, 0x90, 0x90, 0x70, 0x0
__spleen_char_101:
	db 0x0, 0x0, 0x70, 0x90, 0xF0, 0x80, 0x70, 0x0
__spleen_char_102:
	db 0x30, 0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x0
__spleen_char_103:
	db 0x0, 0x0, 0x70, 0x90, 0x90, 0x60, 0x10, 0xE0
__spleen_char_104:
	db 0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0x90, 0x0
__spleen_char_105:
	db 0x0, 0x20, 0x0, 0x60, 0x20, 0x20, 0x30, 0x0
__spleen_char_106:
	db 0x0, 0x20, 0x0, 0x20, 0x20, 0x20, 0x20, 0xC0
__spleen_char_107:
	db 0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x0
__spleen_char_108:
	db 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x30, 0x0
__spleen_char_109:
	db 0x0, 0x0, 0x90, 0xF0, 0xF0, 0x90, 0x90, 0x0
__spleen_char_110:
	db 0x0, 0x0, 0xE0, 0x90, 0x90, 0x90, 0x90, 0x0
__spleen_char_111:
	db 0x0, 0x0, 0x60, 0x90, 0x90, 0x90, 0x60, 0x0
__spleen_char_112:
	db 0x0, 0x0, 0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80
__spleen_char_113:
	db 0x0, 0x0, 0x70, 0x90, 0x90, 0x70, 0x10, 0x10
__spleen_char_114:
	db 0x0, 0x0, 0x70, 0x90, 0x80, 0x80, 0x80, 0x0
__spleen_char_115:
	db 0x0, 0x0, 0x70, 0x80, 0x60, 0x10, 0xE0, 0x0
__spleen_char_116:
	db 0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x30, 0x0
__spleen_char_117:
	db 0x0, 0x0, 0x90, 0x90, 0x90, 0x90, 0x70, 0x0
__spleen_char_118:
	db 0x0, 0x0, 0x90, 0x90, 0x90, 0x60, 0x60, 0x0
__spleen_char_119:
	db 0x0, 0x0, 0x90, 0x90, 0xF0, 0xF0, 0x90, 0x0
__spleen_char_120:
	db 0x0, 0x0, 0x90, 0x60, 0x60, 0x90, 0x90, 0x0
__spleen_char_121:
	db 0x0, 0x0, 0x90, 0x90, 0x90, 0x70, 0x10, 0xE0
__spleen_char_122:
	db 0x0, 0x0, 0xF0, 0x10, 0x20, 0x40, 0xF0, 0x0
__spleen_char_123:
	db 0x30, 0x40, 0x40, 0xC0, 0xC0, 0x40, 0x40, 0x30
__spleen_char_124:
	db 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20
__spleen_char_125:
	db 0xC0, 0x20, 0x20, 0x30, 0x30, 0x20, 0x20, 0xC0
__spleen_char_126:
	db 0x0, 0x0, 0x0, 0x48, 0xB0, 0x0, 0x0, 0x0