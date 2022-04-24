//
// Created by blackberry on 12.01.2021.
//

#ifndef SECP251K1_SANDBOX_CONSTANTS_H
#define SECP251K1_SANDBOX_CONSTANTS_H

#define PREFFERED_BASE                                  16u
#define LSB_HASH_SIZE                                   unsigned long


/// Point generation errors
#define GENERATION_E_OK                                 0u
#define GENERATION_E_UNKNOWN_POINT_KEY                  1u
#define GENERATION_E_TOO_MANY_SLICES                    2u
#define GENERATION_E_TOO_MANY_POINTS_PER_SLICE          3u
#define GENERATION_E_POINTS_OUTSIDE_RANGE               4u
#define GENERATION_E_NO_SLICES                          5u
#define GENERATION_E_POINT_NUMBER_NOT_MATCHING          6u


#define MEMORY_E_OK                                     64u
#define MEMORY_E_VARIABLES_NOT_INITIALIZED              64u


/// File stream errors
#define FILE_E_OK                                       128u
#define FILE_E_NOT_OPEN                                 129u


/// File integrity errors
#define INTEGRITY_E_OK                                  256u
#define INTEGRITY_E_FILETYPE_MISMATCH                   257u
#define INTEGRITY_E_UNKNOWN_FILETYPE                    258u
#define INTEGRITY_E_UNKNOWN_INITIAL_POINT               259u
#define INTEGRITY_E_INVALID_INITIAL_POINT               260u
#define INTEGRITY_E_UNKNOWN_TARGET_POINT                261u
#define INTEGRITY_E_INVALID_TARGET_POINT                262u
#define INTEGRITY_E_UNKNOWN_SLICE_NUMBER                263u
#define INTEGRITY_E_INVALID_SLICE_NUMBER                264u
#define INTEGRITY_E_UNKNOWN_SLICE_SIZE                  265u
#define INTEGRITY_E_UNKNOWN_POINTS_PER_SLICE            266u
#define INTEGRITY_E_INVALID_POINTS_PER_SLICE            267u
#define INTEGRITY_E_UNKNOWN_TOTAL_POINT_NUMBER          268u
#define INTEGRITY_E_INVALID_TOTAL_POINT_NUMBER          269u
#define INTEGRITY_E_UNKNOWN_ITERATIONs_NUMBER           270u
#define INTEGRITY_E_POINT_NUMBERS_NOT_MATCHING          271u
#define INTEGRITY_E_UNKNOWN_INCREMENT_SIZE              272u
#define INTEGRITY_E_SLICE_SIZE_TOO_BIG                  273u
#define INTEGRITY_E_INCREMENT_SIZE_TOO_BIG              274u
#define INTEGRITY_E_UNKNOWN_EOF_TOKEN                   275u
#define INTEGRITY_E_INVALID_EOF_TOKEN                   275u


/// Verbose point generation errors
#define VERBOSE_GENERATION_E_OK                         "Point generation parameters are valid"
#define VERBOSE_GENERATION_E_UNKNOWN_POINT_KEY          "Starting point key is not known"
#define VERBOSE_GENERATION_E_TOO_MANY_SLICES            "Number of slices bigger than the number of desired points"
#define VERBOSE_GENERATION_E_TOO_MANY_POINTS_PER_SLICE  "Number of points per slice too big"
#define VERBOSE_GENERATION_E_POINTS_OUTSIDE_RANGE       "Generated points outside of symmetry range"
#define VERBOSE_GENERATION_E_NO_SLICES                  "There should be at least one number slice"
#define VERBOSE_GENERATION_E_POINT_NUMBER_NOT_MATCHING  "Points per slice and point number should match for continuous generation"


/// File tags
#define UNCOMPRESSED_POINTS_FILE_TAG "UNCOMPRESSED_POINTS_FILE"
#define COMPRESSED_POINTS_FILE_TAG "COMPRESSED_POINTS_FILE"
#define HASHED_POINTS_FILE_TAG "HASH_POINTS_FILE"
#define CHECKPOINT_FILE_TAG "CHECKPOINT_FILE"
#define STARTING_POINT_TAG "STARTING_POINT"
#define TARGET_POINT_TAG "TARGET_POINT"
#define SLICE_NUMBER_TAG "NUMBER_OF_SLICES"
#define SLICE_SIZE_TAG "SLICE_SIZE"
#define POINTS_PER_SLICE_TAG "POINTS_PER_sLICE"
#define TOTAL_POINT_NUMBER_TAG "TOTAL_POINTS"
#define ITERATION_NUMBER_TAG "ITERATION_NUMBER"
#define INCREMENT_SIZE_TAG "INCREMENT_SIZE"
#define EOF_TAG "EOF"
#define GENERATED_POINTS_EOF_TAG "GENERATED_POINTS_EOF"
#define CHECKPOINT_EOF_TAG "CHECKPOINT_EOF"


/// Known file types
#define FILETYPE_UNCOMPRESSED_POINTS                    0u
#define FILETYPE_COMPRESSED_POINTS                      1u
#define FILETYPE_HASHED_POINTS                          2u
#define FILETYPE_CHECKPOINT                             3u
#define FILETYPE_UNKNOWN                                4u


///Elliptic Curve Parameters
#define moduloHalb_String "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFE17"
#define order_String "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define orderMinusOneDivTwo_String "7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF5D576E7357A4501DDFE92F46681B20A0"
#define prime_String "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define primeMinusOne_String "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2E"
#define primePlusOneDivFour_String "3FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFFF0C"
#define kG_String "1"


/// G multiples

/// G * 2^0
#define xG_String "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798"
#define yG_String "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"

/// TODO: add the multiples of G for efficient multiplication
/// G * 2^1
/// G * 2^2
/// G * 2^3
/// G * 2^4
/// G * 2^5
/// G * 2^6
/// G * 2^7
/// G * 2^8
/// G * 2^9
/// G * 2^10
/// G * 2^11
/// G * 2^12
/// G * 2^13
/// G * 2^14
/// G * 2^15
/// G * 2^16
/// G * 2^17
/// G * 2^18
/// G * 2^19
/// G * 2^20
/// G * 2^21
/// G * 2^22
/// G * 2^23
/// G * 2^24
/// G * 2^25
/// G * 2^26
/// G * 2^27
/// G * 2^28
/// G * 2^29
/// G * 2^30
/// G * 2^31
/// G * 2^32
/// G * 2^33
/// G * 2^34
/// G * 2^35
/// G * 2^36
/// G * 2^37
/// G * 2^38
/// G * 2^39
/// G * 2^40
/// G * 2^41
/// G * 2^42
/// G * 2^43
/// G * 2^44
/// G * 2^45
/// G * 2^46
/// G * 2^47
/// G * 2^48
/// G * 2^49
/// G * 2^50
/// G * 2^51
/// G * 2^52
/// G * 2^53
/// G * 2^54
/// G * 2^55
/// G * 2^56
/// G * 2^57
/// G * 2^58
/// G * 2^59
/// G * 2^60
/// G * 2^61
/// G * 2^62
/// G * 2^63
/// G * 2^64
/// G * 2^65
/// G * 2^66
/// G * 2^67
/// G * 2^68
/// G * 2^69
/// G * 2^70
/// G * 2^71
/// G * 2^72
/// G * 2^73
/// G * 2^74
/// G * 2^75
/// G * 2^76
/// G * 2^77
/// G * 2^78
/// G * 2^79
/// G * 2^80
/// G * 2^81
/// G * 2^82
/// G * 2^83
/// G * 2^84
/// G * 2^85
/// G * 2^86
/// G * 2^87
/// G * 2^88
/// G * 2^89
/// G * 2^90
/// G * 2^91
/// G * 2^92
/// G * 2^93
/// G * 2^94
/// G * 2^95
/// G * 2^96
/// G * 2^97
/// G * 2^98
/// G * 2^99
/// G * 2^100
/// G * 2^101
/// G * 2^102
/// G * 2^103
/// G * 2^104
/// G * 2^105
/// G * 2^106
/// G * 2^107
/// G * 2^108
/// G * 2^109
/// G * 2^110
/// G * 2^111
/// G * 2^112
/// G * 2^113
/// G * 2^114
/// G * 2^115
/// G * 2^116
/// G * 2^117
/// G * 2^118
/// G * 2^119
/// G * 2^120
/// G * 2^121
/// G * 2^122
/// G * 2^123
/// G * 2^124
/// G * 2^125
/// G * 2^126
/// G * 2^127
/// G * 2^128
/// G * 2^129
/// G * 2^130
/// G * 2^131
/// G * 2^132
/// G * 2^133
/// G * 2^134
/// G * 2^135
/// G * 2^136
/// G * 2^137
/// G * 2^138
/// G * 2^139
/// G * 2^140
/// G * 2^141
/// G * 2^142
/// G * 2^143
/// G * 2^144
/// G * 2^145
/// G * 2^146
/// G * 2^147
/// G * 2^148
/// G * 2^149
/// G * 2^150
/// G * 2^151
/// G * 2^152
/// G * 2^153
/// G * 2^154
/// G * 2^155
/// G * 2^156
/// G * 2^157
/// G * 2^158
/// G * 2^159
/// G * 2^160
/// G * 2^161
/// G * 2^162
/// G * 2^163
/// G * 2^164
/// G * 2^165
/// G * 2^166
/// G * 2^167
/// G * 2^168
/// G * 2^169
/// G * 2^170
/// G * 2^171
/// G * 2^172
/// G * 2^173
/// G * 2^174
/// G * 2^175
/// G * 2^176
/// G * 2^177
/// G * 2^178
/// G * 2^179
/// G * 2^180
/// G * 2^181
/// G * 2^182
/// G * 2^183
/// G * 2^184
/// G * 2^185
/// G * 2^186
/// G * 2^187
/// G * 2^188
/// G * 2^189
/// G * 2^190
/// G * 2^191
/// G * 2^192
/// G * 2^193
/// G * 2^194
/// G * 2^195
/// G * 2^196
/// G * 2^197
/// G * 2^198
/// G * 2^199
/// G * 2^200
/// G * 2^201
/// G * 2^202
/// G * 2^203
/// G * 2^204
/// G * 2^205
/// G * 2^206
/// G * 2^207
/// G * 2^208
/// G * 2^209
/// G * 2^210
/// G * 2^211
/// G * 2^212
/// G * 2^213
/// G * 2^214
/// G * 2^215
/// G * 2^216
/// G * 2^217
/// G * 2^218
/// G * 2^219
/// G * 2^220
/// G * 2^221
/// G * 2^222
/// G * 2^223
/// G * 2^224
/// G * 2^225
/// G * 2^226
/// G * 2^227
/// G * 2^228
/// G * 2^229
/// G * 2^230
/// G * 2^231
/// G * 2^232
/// G * 2^233
/// G * 2^234
/// G * 2^235
/// G * 2^236
/// G * 2^237
/// G * 2^238
/// G * 2^239
/// G * 2^240
/// G * 2^241
/// G * 2^242
/// G * 2^243
/// G * 2^244
/// G * 2^245
/// G * 2^246
/// G * 2^247
/// G * 2^248
/// G * 2^249
/// G * 2^250
/// G * 2^251
/// G * 2^252
/// G * 2^253
/// G * 2^254
/// G * 2^255
/// G * 2^256

#endif //SECP251K1_SANDBOX_CONSTANTS_H
