/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2013 Bruno Morelli
 */

#ifndef GIC_INTERNAL_PRIO_MAP_H__
#define GIC_INTERNAL_PRIO_MAP_H__

#define EE_ISR_PRI_1         1
#define EE_ISR_PRI_2         2
#define EE_ISR_PRI_3         3
#define EE_ISR_PRI_4         4
#define EE_ISR_PRI_5         5
#define EE_ISR_PRI_6         6
#define EE_ISR_PRI_7         7
#define EE_ISR_PRI_8         8
#define EE_ISR_PRI_9         9
#define EE_ISR_PRI_10       10
#define EE_ISR_PRI_11       11
#define EE_ISR_PRI_12       12
#define EE_ISR_PRI_13       13
#define EE_ISR_PRI_14       14
#define EE_ISR_PRI_15       15
#define EE_ISR_PRI_16       16
#define EE_ISR_PRI_17       17
#define EE_ISR_PRI_18       18
#define EE_ISR_PRI_19       19
#define EE_ISR_PRI_20       20
#define EE_ISR_PRI_21       21
#define EE_ISR_PRI_22       22
#define EE_ISR_PRI_23       23
#define EE_ISR_PRI_24       24
#define EE_ISR_PRI_25       25
#define EE_ISR_PRI_26       26
#define EE_ISR_PRI_27       27
#define EE_ISR_PRI_28       28
#define EE_ISR_PRI_29       29
#define EE_ISR_PRI_30       30
#define EE_ISR_PRI_31       31
#define EE_ISR_PRI_32       32
#define EE_ISR_PRI_33       33
#define EE_ISR_PRI_34       34
#define EE_ISR_PRI_35       35
#define EE_ISR_PRI_36       36
#define EE_ISR_PRI_37       37
#define EE_ISR_PRI_38       38
#define EE_ISR_PRI_39       39
#define EE_ISR_PRI_40       40
#define EE_ISR_PRI_41       41
#define EE_ISR_PRI_42       42
#define EE_ISR_PRI_43       43
#define EE_ISR_PRI_44       44
#define EE_ISR_PRI_45       45
#define EE_ISR_PRI_46       46
#define EE_ISR_PRI_47       47
#define EE_ISR_PRI_48       48
#define EE_ISR_PRI_49       49
#define EE_ISR_PRI_50       50
#define EE_ISR_PRI_51       51
#define EE_ISR_PRI_52       52
#define EE_ISR_PRI_53       53
#define EE_ISR_PRI_54       54
#define EE_ISR_PRI_55       55
#define EE_ISR_PRI_56       56
#define EE_ISR_PRI_57       57
#define EE_ISR_PRI_58       58
#define EE_ISR_PRI_59       59
#define EE_ISR_PRI_60       60
#define EE_ISR_PRI_61       61
#define EE_ISR_PRI_62       62
#define EE_ISR_PRI_63       63
#define EE_ISR_PRI_64       64
#define EE_ISR_PRI_65       65
#define EE_ISR_PRI_66       66
#define EE_ISR_PRI_67       67
#define EE_ISR_PRI_68       68
#define EE_ISR_PRI_69       69
#define EE_ISR_PRI_70       70
#define EE_ISR_PRI_71       71
#define EE_ISR_PRI_72       72
#define EE_ISR_PRI_73       73
#define EE_ISR_PRI_74       74
#define EE_ISR_PRI_75       75
#define EE_ISR_PRI_76       76
#define EE_ISR_PRI_77       77
#define EE_ISR_PRI_78       78
#define EE_ISR_PRI_79       79
#define EE_ISR_PRI_80       80
#define EE_ISR_PRI_81       81
#define EE_ISR_PRI_82       82
#define EE_ISR_PRI_83       83
#define EE_ISR_PRI_84       84
#define EE_ISR_PRI_85       85
#define EE_ISR_PRI_86       86
#define EE_ISR_PRI_87       87
#define EE_ISR_PRI_88       88
#define EE_ISR_PRI_89       89
#define EE_ISR_PRI_90       90
#define EE_ISR_PRI_91       91
#define EE_ISR_PRI_92       92
#define EE_ISR_PRI_93       93
#define EE_ISR_PRI_94       94
#define EE_ISR_PRI_95       95
#define EE_ISR_PRI_96       96
#define EE_ISR_PRI_97       97
#define EE_ISR_PRI_98       98
#define EE_ISR_PRI_99       99
#define EE_ISR_PRI_100     100
#define EE_ISR_PRI_101     101
#define EE_ISR_PRI_102     102
#define EE_ISR_PRI_103     103
#define EE_ISR_PRI_104     104
#define EE_ISR_PRI_105     105
#define EE_ISR_PRI_106     106
#define EE_ISR_PRI_107     107
#define EE_ISR_PRI_108     108
#define EE_ISR_PRI_109     109
#define EE_ISR_PRI_110     110
#define EE_ISR_PRI_111     111
#define EE_ISR_PRI_112     112
#define EE_ISR_PRI_113     113
#define EE_ISR_PRI_114     114
#define EE_ISR_PRI_115     115
#define EE_ISR_PRI_116     116
#define EE_ISR_PRI_117     117
#define EE_ISR_PRI_118     118
#define EE_ISR_PRI_119     119
#define EE_ISR_PRI_120     120
#define EE_ISR_PRI_121     121
#define EE_ISR_PRI_122     122
#define EE_ISR_PRI_123     123
#define EE_ISR_PRI_124     124
#define EE_ISR_PRI_125     125
#define EE_ISR_PRI_126     126
#define EE_ISR_PRI_127     127
#define EE_ISR_PRI_128     128
#define EE_ISR_PRI_129     129
#define EE_ISR_PRI_130     130
#define EE_ISR_PRI_131     131
#define EE_ISR_PRI_132     132
#define EE_ISR_PRI_133     133
#define EE_ISR_PRI_134     134
#define EE_ISR_PRI_135     135
#define EE_ISR_PRI_136     136
#define EE_ISR_PRI_137     137
#define EE_ISR_PRI_138     138
#define EE_ISR_PRI_139     139
#define EE_ISR_PRI_140     140
#define EE_ISR_PRI_141     141
#define EE_ISR_PRI_142     142
#define EE_ISR_PRI_143     143
#define EE_ISR_PRI_144     144
#define EE_ISR_PRI_145     145
#define EE_ISR_PRI_146     146
#define EE_ISR_PRI_147     147
#define EE_ISR_PRI_148     148
#define EE_ISR_PRI_149     149
#define EE_ISR_PRI_150     150
#define EE_ISR_PRI_151     151
#define EE_ISR_PRI_152     152
#define EE_ISR_PRI_153     153
#define EE_ISR_PRI_154     154
#define EE_ISR_PRI_155     155
#define EE_ISR_PRI_156     156
#define EE_ISR_PRI_157     157
#define EE_ISR_PRI_158     158
#define EE_ISR_PRI_159     159
#define EE_ISR_PRI_160     160
#define EE_ISR_PRI_161     161
#define EE_ISR_PRI_162     162
#define EE_ISR_PRI_163     163
#define EE_ISR_PRI_164     164
#define EE_ISR_PRI_165     165
#define EE_ISR_PRI_166     166
#define EE_ISR_PRI_167     167
#define EE_ISR_PRI_168     168
#define EE_ISR_PRI_169     169
#define EE_ISR_PRI_170     170
#define EE_ISR_PRI_171     171
#define EE_ISR_PRI_172     172
#define EE_ISR_PRI_173     173
#define EE_ISR_PRI_174     174
#define EE_ISR_PRI_175     175
#define EE_ISR_PRI_176     176
#define EE_ISR_PRI_177     177
#define EE_ISR_PRI_178     178
#define EE_ISR_PRI_179     179
#define EE_ISR_PRI_180     180
#define EE_ISR_PRI_181     181
#define EE_ISR_PRI_182     182
#define EE_ISR_PRI_183     183
#define EE_ISR_PRI_184     184
#define EE_ISR_PRI_185     185
#define EE_ISR_PRI_186     186
#define EE_ISR_PRI_187     187
#define EE_ISR_PRI_188     188
#define EE_ISR_PRI_189     189
#define EE_ISR_PRI_190     190
#define EE_ISR_PRI_191     191
#define EE_ISR_PRI_192     192
#define EE_ISR_PRI_193     193
#define EE_ISR_PRI_194     194
#define EE_ISR_PRI_195     195
#define EE_ISR_PRI_196     196
#define EE_ISR_PRI_197     197
#define EE_ISR_PRI_198     198
#define EE_ISR_PRI_199     199
#define EE_ISR_PRI_200     200
#define EE_ISR_PRI_201     201
#define EE_ISR_PRI_202     202
#define EE_ISR_PRI_203     203
#define EE_ISR_PRI_204     204
#define EE_ISR_PRI_205     205
#define EE_ISR_PRI_206     206
#define EE_ISR_PRI_207     207
#define EE_ISR_PRI_208     208
#define EE_ISR_PRI_209     209
#define EE_ISR_PRI_210     210
#define EE_ISR_PRI_211     211
#define EE_ISR_PRI_212     212
#define EE_ISR_PRI_213     213
#define EE_ISR_PRI_214     214
#define EE_ISR_PRI_215     215
#define EE_ISR_PRI_216     216
#define EE_ISR_PRI_217     217
#define EE_ISR_PRI_218     218
#define EE_ISR_PRI_219     219
#define EE_ISR_PRI_220     220
#define EE_ISR_PRI_221     221
#define EE_ISR_PRI_222     222
#define EE_ISR_PRI_223     223
#define EE_ISR_PRI_224     224
#define EE_ISR_PRI_225     225
#define EE_ISR_PRI_226     226
#define EE_ISR_PRI_227     227
#define EE_ISR_PRI_228     228
#define EE_ISR_PRI_229     229
#define EE_ISR_PRI_230     230
#define EE_ISR_PRI_231     231
#define EE_ISR_PRI_232     232
#define EE_ISR_PRI_233     233
#define EE_ISR_PRI_234     234
#define EE_ISR_PRI_235     235
#define EE_ISR_PRI_236     236
#define EE_ISR_PRI_237     237
#define EE_ISR_PRI_238     238
#define EE_ISR_PRI_239     239
#define EE_ISR_PRI_240     240
#define EE_ISR_PRI_241     241
#define EE_ISR_PRI_242     242
#define EE_ISR_PRI_243     243
#define EE_ISR_PRI_244     244
#define EE_ISR_PRI_245     245
#define EE_ISR_PRI_246     246
#define EE_ISR_PRI_247     247
#define EE_ISR_PRI_248     248
#define EE_ISR_PRI_249     249
#define EE_ISR_PRI_250     250
#define EE_ISR_PRI_251     251
#define EE_ISR_PRI_252     252
#define EE_ISR_PRI_253     253
#define EE_ISR_PRI_254     254
#define EE_ISR_PRI_255     255

#endif /* GIC_INTERNAL_PRIO_MAP_H__ */
