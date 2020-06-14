//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Created by werner on 12.04.20.
// Copyright (c) 2020 Werner Dittmann. All rights reserved.
//

#include "../logging/ZrtpLogging.h"
#include "gtest/gtest.h"
#include "../common/Utilities.h"

#include "botan_all.h"

// The data was copied from Skein's test vectors, contained on the official Skein NIST CD

//:Skein-512:  1024-bit hash, msgLen =  1024 bits, data = 'zero'
//
//Message data:
static std::array<unsigned char, 128> tf_1024h_0_In = {
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00
};
// Result:
static std::array<unsigned char, 128> tf_1024h_0_Out = {
        0x4F, 0xC4, 0x31, 0x53,  0x37, 0x41, 0x6A, 0x60,  0x15, 0x74, 0xC3, 0x77,  0x20, 0x5A, 0xC5, 0x17,
        0x23, 0x5D, 0xAE, 0x3D,  0x39, 0xC8, 0x48, 0x5E,  0xA5, 0x19, 0x08, 0xAC,  0x86, 0xFB, 0x43, 0x55,
        0xD8, 0x5C, 0xE6, 0xBC,  0x6F, 0x2B, 0x65, 0x38,  0xD9, 0xBD, 0xB0, 0x8B,  0x69, 0x4F, 0x8F, 0xDA,
        0x4E, 0x46, 0x64, 0x2A,  0xEE, 0x61, 0x43, 0x84,  0x28, 0xE6, 0xEE, 0x7E,  0xC1, 0xF9, 0x4E, 0xAD,
        0xC0, 0x09, 0x96, 0xF3,  0xA4, 0x41, 0xAA, 0xA9,  0x1C, 0x96, 0xC1, 0x91,  0x67, 0xF1, 0xAB, 0x21,
        0x0B, 0x6C, 0x99, 0xAB,  0x3D, 0x64, 0x95, 0x92,  0x16, 0x6F, 0x74, 0x20,  0xA9, 0x94, 0xC9, 0xBD,
        0x32, 0xBC, 0xCD, 0xE2,  0x63, 0x91, 0xB0, 0x9C,  0xEB, 0x81, 0x5E, 0x2A,  0x12, 0xE3, 0xDF, 0x80,
        0x60, 0x5D, 0x70, 0x78,  0xFB, 0x1B, 0x8F, 0xCA,  0xF0, 0x1B, 0x17, 0x54,  0xCC, 0x27, 0x1B, 0x6E
};

//:Skein-512:   520-bit hash, msgLen =  1024 bits, data = 'zero'
//
//Message data:
static std::array<unsigned char, 128> tf_520h_0_In = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// Result:
static std::array<unsigned char, 65> tf_520h_0_Out = {
        0xC7, 0x78, 0x61, 0xB1, 0xFC, 0xE6, 0x7C, 0x93, 0x63, 0x09, 0x68, 0xF2, 0x1F, 0x9E, 0x3D, 0x0C,
        0x24, 0xD3, 0x47, 0x0E, 0xCE, 0xE2, 0x05, 0xEC, 0x56, 0x19, 0x2F, 0x23, 0x00, 0xE4, 0x3B, 0x56,
        0xD3, 0xC0, 0x63, 0xF6, 0x59, 0x68, 0x75, 0x09, 0x2A, 0x10, 0x8E, 0x8A, 0xD3, 0x4C, 0x42, 0x0B,
        0xC2, 0xF6, 0x97, 0x8D, 0x4F, 0x3C, 0x2B, 0xB6, 0xE5, 0x39, 0x49, 0xA5, 0x06, 0x51, 0xE0, 0x0E,
        0x2D
};

//:Skein-512:  1032-bit hash, msgLen =  1024 bits, data = 'zero'
//
//Message data:
static std::array<unsigned char, 128> tf_1032h_0_In = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// Result:
static std::array<unsigned char, 129> tf_1032h_0_Out = {
        0xA9, 0x75, 0x80, 0x15, 0xF0, 0x89, 0x2C, 0x5C, 0xFE, 0x64, 0x86, 0x04, 0xBA, 0x7C, 0xC4, 0x87,
        0xFB, 0x6A, 0xCB, 0x74, 0xB8, 0xAE, 0xC2, 0x8D, 0xCF, 0x24, 0xA4, 0x41, 0x1C, 0xCD, 0x46, 0x39,
        0xB6, 0x02, 0x2C, 0xCA, 0x7A, 0x11, 0xF8, 0xB3, 0xEC, 0xD3, 0xE4, 0xFB, 0xE5, 0x23, 0xB0, 0xF7,
        0xAC, 0xF0, 0x3C, 0x57, 0xFD, 0x22, 0xCD, 0xA2, 0x8E, 0xEE, 0x38, 0x95, 0x67, 0x14, 0x95, 0x02,
        0xB2, 0x55, 0x83, 0x14, 0x79, 0x2B, 0x6C, 0x01, 0xEB, 0x72, 0x50, 0xE0, 0x4F, 0x79, 0x4D, 0xD6,
        0xCA, 0x62, 0xFF, 0xEC, 0xEA, 0x43, 0xB2, 0x29, 0xE3, 0x1A, 0xB3, 0x9D, 0x3B, 0x16, 0x01, 0x95,
        0x85, 0x47, 0xFB, 0x13, 0x3B, 0x38, 0x7C, 0xE9, 0x86, 0xA1, 0x12, 0xB6, 0x53, 0x5F, 0xC5, 0x82,
        0x67, 0xDB, 0x07, 0xBC, 0x0B, 0xE6, 0x19, 0xBA, 0xD0, 0x7F, 0xC6, 0xD3, 0xF5, 0x53, 0x79, 0xB2,
        0x17
};


//     :Skein-512:  1024-bit hash, msgLen =  1024 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 128> tf_1024h_D_In = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
        0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
        0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
        0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
        0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
        0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
        0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
        0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80
};
// Result:
static std::array<unsigned char, 128> tf_1024h_D_Out = {
        0xBE, 0x71, 0x89, 0x13, 0x53, 0xE1, 0x57, 0xD8, 0x55, 0x70, 0x07, 0xE6, 0xC4, 0xDB, 0x77, 0x42,
        0xA8, 0xE9, 0x4D, 0x26, 0x77, 0xB8, 0xBF, 0x13, 0x8E, 0x0E, 0x74, 0x7D, 0x4F, 0x70, 0x24, 0xBA,
        0x5E, 0x9D, 0x53, 0x1D, 0xB0, 0xB6, 0xCB, 0x41, 0x26, 0x77, 0x68, 0x5B, 0x9F, 0x9B, 0x0A, 0x7F,
        0xCD, 0x42, 0x99, 0xC5, 0xD5, 0x08, 0x51, 0x25, 0x34, 0x7B, 0x59, 0xA4, 0x7B, 0xEA, 0xFD, 0x6B,
        0xD2, 0xD7, 0xC9, 0xDE, 0x07, 0xCC, 0xE0, 0x77, 0x01, 0xC5, 0xD0, 0xCE, 0x3C, 0x3A, 0x8F, 0x75,
        0xE0, 0xA8, 0xC1, 0x6E, 0x1A, 0xAD, 0xB2, 0x92, 0x98, 0x21, 0x99, 0x69, 0xDA, 0x77, 0xC5, 0x2C,
        0xBF, 0x8D, 0xD8, 0xCF, 0x86, 0xA9, 0xE1, 0xB0, 0xBB, 0x7D, 0x18, 0x15, 0x3D, 0x70, 0xEE, 0x5C,
        0x26, 0x60, 0x6D, 0x92, 0x2D, 0x91, 0x5C, 0x05, 0xDA, 0x41, 0xD6, 0x4F, 0xDE, 0xB4, 0x21, 0x50
};

//:Skein-512:   520-bit hash, msgLen =  1024 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 128> tf_520h_D_In = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
        0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
        0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
        0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
        0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
        0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
        0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
        0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80
};
// Result:
static std::array<unsigned char, 65> tf_520h_D_Out = {
        0x9E, 0x65, 0x5B, 0x72, 0x5A, 0xC0, 0x96, 0x43, 0xC4, 0x49, 0xC7, 0x24, 0xC6, 0xB1, 0x19, 0x7D,
        0xDC, 0xF7, 0xD4, 0x2B, 0x8B, 0xC9, 0xEF, 0x80, 0x47, 0x63, 0x0A, 0xB3, 0x84, 0x8C, 0x39, 0xC7,
        0x8E, 0xE5, 0xF0, 0x60, 0xF7, 0x01, 0x86, 0x39, 0xE2, 0x02, 0x01, 0xC7, 0xD8, 0x6E, 0xEF, 0xE9,
        0x84, 0x52, 0xD7, 0xCF, 0xC2, 0x43, 0x5E, 0xDE, 0xCA, 0x9A, 0x4E, 0x1A, 0xEC, 0x3E, 0x9D, 0xC9,
        0x3F
};

//:Skein-512:  1032-bit hash, msgLen =  1024 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 128> tf_1032h_D_In = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
        0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
        0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
        0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
        0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
        0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
        0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
        0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80
};
// Result:
static std::array<unsigned char, 129> tf_1032h_D_Out = {
        0x23, 0xB7, 0xD7, 0x8C, 0xBB, 0x97, 0x69, 0xBD, 0x23, 0xB0, 0x86, 0x75, 0xBD, 0x87, 0xF2, 0xC7,
        0xAF, 0x44, 0x47, 0x04, 0x72, 0x8A, 0x1A, 0xF4, 0xC8, 0x5F, 0xE1, 0xC0, 0x84, 0x9D, 0xBA, 0x48,
        0xB3, 0x6C, 0x87, 0x39, 0xD2, 0x41, 0xA2, 0xC6, 0xD9, 0x63, 0xE7, 0xE8, 0x40, 0x1B, 0x8C, 0xE3,
        0xC9, 0xBC, 0x2F, 0x1D, 0x4F, 0x93, 0x69, 0x98, 0x85, 0xB5, 0x34, 0x39, 0xB9, 0x06, 0xAC, 0xEB,
        0x2E, 0x9D, 0x9B, 0x11, 0x56, 0xE9, 0x7E, 0x3D, 0x9B, 0x9E, 0x8E, 0xA9, 0x46, 0x88, 0xD2, 0xE5,
        0xF5, 0xD9, 0x9C, 0x4C, 0x64, 0x19, 0x67, 0xC9, 0xC0, 0x26, 0xED, 0xF3, 0xF9, 0xE1, 0x25, 0x97,
        0x6E, 0x1B, 0x30, 0x05, 0x31, 0x7B, 0xBE, 0xBC, 0x84, 0xA4, 0xC1, 0xA0, 0xF6, 0x4C, 0x76, 0x1C,
        0xF8, 0x69, 0x66, 0x0C, 0xC1, 0x8D, 0x3B, 0xA7, 0x0F, 0x8D, 0xB9, 0x5E, 0xE5, 0xF6, 0x17, 0x0B,
        0x16
};

//:Skein-512:   512-bit hash, msgLen =     1 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_1Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_1Bit_Out = {
        0x54, 0xEA, 0xEA, 0x3E, 0xD9, 0xF3, 0x34, 0x01, 0xBA, 0x8A, 0xF6, 0x45, 0xB3, 0xD3, 0x80, 0xFC,
        0x40, 0x2E, 0x61, 0xB4, 0x3B, 0x84, 0xED, 0x26, 0xB3, 0xD1, 0xE9, 0x80, 0x72, 0xA4, 0xB0, 0x29,
        0xCA, 0xD8, 0x6E, 0xDB, 0xDC, 0x17, 0x34, 0x3B, 0xAD, 0xA6, 0x27, 0x0D, 0x9E, 0xEB, 0xB0, 0x44,
        0x17, 0x25, 0xAF, 0xEA, 0x51, 0xAD, 0x74, 0xF0, 0x43, 0xCD, 0x25, 0x4B, 0xBC, 0xCE, 0x2C, 0xB7
};

//
//:Skein-512:   512-bit hash, msgLen =     2 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_2Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_2Bit_Out = {
        0xB0, 0x55, 0xF4, 0x35, 0xFF, 0x61, 0x15, 0x13, 0x2E, 0xF7, 0x71, 0xBF, 0xF1, 0xE3, 0x82, 0x04,
        0x3D, 0x93, 0xBE, 0x94, 0xAD, 0x3E, 0x2E, 0x17, 0x15, 0xE6, 0x15, 0x86, 0x32, 0x2C, 0x5E, 0x25,
        0x99, 0xC8, 0x8B, 0x1E, 0x48, 0x3C, 0x22, 0x2D, 0xEB, 0x44, 0x86, 0x68, 0xC4, 0x1C, 0xBD, 0x48,
        0xDE, 0x27, 0x03, 0x93, 0x1C, 0x98, 0x6D, 0x3F, 0xC0, 0xD6, 0x8F, 0xB9, 0x00, 0x87, 0xE3, 0x40
};

//
//:Skein-512:   512-bit hash, msgLen =     3 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_3Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_3Bit_Out = {
        0xFC, 0xAB, 0xD6, 0x46, 0x33, 0xC0, 0x1B, 0x1F, 0x51, 0x80, 0x32, 0x1C, 0x3A, 0x73, 0x4D, 0x37,
        0x58, 0xCB, 0xD7, 0x35, 0xFC, 0x4A, 0x77, 0xF4, 0x32, 0xE2, 0xD0, 0xC9, 0x9E, 0x5A, 0xF2, 0x8D,
        0xAF, 0x26, 0x9D, 0xCC, 0xB3, 0x4A, 0x74, 0x35, 0xE9, 0x31, 0x15, 0x7E, 0x49, 0xB8, 0xD2, 0xE3,
        0xEE, 0xD0, 0xFC, 0xFA, 0xB7, 0x1F, 0x16, 0x33, 0xD8, 0x89, 0xE6, 0x54, 0x28, 0xD9, 0x52, 0x42
};

//
//:Skein-512:   512-bit hash, msgLen =     4 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_4Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_4Bit_Out = {
        0x15, 0x6E, 0x61, 0xBF, 0x4C, 0x11, 0x04, 0x6E, 0x64, 0x3B, 0x86, 0x86, 0xC4, 0xBD, 0x85, 0xB6,
        0xC7, 0x85, 0xDD, 0xA5, 0xB4, 0x66, 0x94, 0x3D, 0xDF, 0xD6, 0x1E, 0x4C, 0xAC, 0x05, 0xEC, 0xCC,
        0xB9, 0xB8, 0x2B, 0x27, 0x77, 0x69, 0x29, 0xF4, 0xA3, 0x39, 0xAD, 0x7F, 0x9A, 0x39, 0x91, 0xAF,
        0xE3, 0xE4, 0x9A, 0x3A, 0x40, 0x7E, 0x0E, 0x7A, 0x75, 0xE5, 0x92, 0x87, 0xDE, 0xF2, 0xF8, 0x99
};

//
//:Skein-512:   512-bit hash, msgLen =     5 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_5Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_5Bit_Out = {
        0x18, 0x5C, 0x59, 0xDC, 0x2F, 0x1B, 0x49, 0xD3, 0x92, 0x04, 0x20, 0x41, 0xCC, 0xF8, 0xC3, 0xB2,
        0x01, 0x69, 0x22, 0x59, 0x70, 0x4A, 0x90, 0xF7, 0x50, 0xDA, 0x33, 0xDA, 0xE8, 0xE6, 0x01, 0x61,
        0x9A, 0x5E, 0x7B, 0xCB, 0x2A, 0x72, 0x31, 0x97, 0xD2, 0x48, 0xE8, 0x05, 0xAB, 0x0F, 0x20, 0x9A,
        0x34, 0x01, 0xFB, 0x6F, 0xB6, 0x71, 0x34, 0xEE, 0x3A, 0x0F, 0xEC, 0x77, 0xF0, 0x6F, 0x41, 0x6E
};

//:Skein-512:   512-bit hash, msgLen =     7 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_7Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_7Bit_Out = {
        0x5F, 0x01, 0xA2, 0xC2, 0x63, 0x45, 0x0D, 0xCB, 0xF5, 0x29, 0x24, 0x21, 0xA9, 0xD0, 0x16, 0x10,
        0x6B, 0x3E, 0xDD, 0x0D, 0xCF, 0x79, 0x61, 0x41, 0xDB, 0xCF, 0x5D, 0x5D, 0xE3, 0xA1, 0x8E, 0xA9,
        0xB6, 0x65, 0x07, 0xDE, 0xA4, 0x78, 0x4A, 0x7C, 0x19, 0x7B, 0xD1, 0x47, 0x69, 0x63, 0x8D, 0x56,
        0x76, 0x36, 0x94, 0x35, 0x52, 0x98, 0xD3, 0x0A, 0x7D, 0x45, 0x77, 0x72, 0x9B, 0xF0, 0x60, 0x16
};

//:Skein-512:   512-bit hash, msgLen =     8 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_8Bit_In = { 0xFF };

// Result:
static std::array<unsigned char, 64> tf_512h_8Bit_Out = {
        0x71, 0xB7, 0xBC, 0xE6, 0xFE, 0x64, 0x52, 0x22, 0x7B, 0x9C, 0xED, 0x60, 0x14, 0x24, 0x9E, 0x5B,
        0xF9, 0xA9, 0x75, 0x4C, 0x3A, 0xD6, 0x18, 0xCC, 0xC4, 0xE0, 0xAA, 0xE1, 0x6B, 0x31, 0x6C, 0xC8,
        0xCA, 0x69, 0x8D, 0x86, 0x43, 0x07, 0xED, 0x3E, 0x80, 0xB6, 0xEF, 0x15, 0x70, 0x81, 0x2A, 0xC5,
        0x27, 0x2D, 0xC4, 0x09, 0xB5, 0xA0, 0x12, 0xDF, 0x2A, 0x57, 0x91, 0x02, 0xF3, 0x40, 0x61, 0x7A
};

//:Skein-512:   512-bit hash, msgLen =     9 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 2> tf_512h_9Bit_In = { 0xFF, 0xfE };

// Result:
static std::array<unsigned char, 64> tf_512h_9Bit_Out = {
        0xF2, 0x3B, 0x93, 0xDB, 0xE9, 0xA9, 0x0B, 0x29, 0xEB, 0xE8, 0xB1, 0xFE, 0xA0, 0xD6, 0x36, 0x18,
        0x2B, 0xD6, 0xCA, 0xF4, 0x16, 0x92, 0xF0, 0x37, 0x71, 0x45, 0x24, 0xF4, 0xEE, 0x3D, 0x76, 0x7E,
        0xB7, 0xD6, 0x8D, 0x39, 0xF4, 0x3E, 0xB8, 0xF1, 0xF9, 0x26, 0x4F, 0x34, 0xF5, 0x1F, 0x17, 0xA7,
        0x95, 0x90, 0x6D, 0xD2, 0xB6, 0x18, 0x3B, 0x74, 0xCB, 0x75, 0xE2, 0x69, 0x17, 0x2D, 0x4F, 0x7D
};

//:Skein-512:   512-bit hash, msgLen =   512 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 64> tf_512h_512Bit_In = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
        0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
        0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
        0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0
};

// Result:
static std::array<unsigned char, 64> tf_512h_512Bit_Out = {
        0x45, 0x86, 0x3B, 0xA3, 0xBE, 0x0C, 0x4D, 0xFC, 0x27, 0xE7, 0x5D, 0x35, 0x84, 0x96, 0xF4, 0xAC,
        0x9A, 0x73, 0x6A, 0x50, 0x5D, 0x93, 0x13, 0xB4, 0x2B, 0x2F, 0x5E, 0xAD, 0xA7, 0x9F, 0xC1, 0x7F,
        0x63, 0x86, 0x1E, 0x94, 0x7A, 0xFB, 0x1D, 0x05, 0x6A, 0xA1, 0x99, 0x57, 0x5A, 0xD3, 0xF8, 0xC9,
        0xA3, 0xCC, 0x17, 0x80, 0xB5, 0xE5, 0xFA, 0x4C, 0xAE, 0x05, 0x0E, 0x98, 0x98, 0x76, 0x62, 0x5B
};

//:Skein-512:   512-bit hash, msgLen =   513 bits, data = 'incrementing'
//
//Message data:
static std::array<unsigned char, 65> tf_512h_513Bit_In = {
        0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
        0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
        0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
        0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
        0xBF
};

// Result:
static std::array<unsigned char, 64> tf_512h_513Bit_Out = {
        0x38, 0xE8, 0xA3, 0x4D, 0x90, 0xA2, 0x44, 0xA6, 0xD7, 0x3F, 0xA6, 0xA8, 0xEC, 0xD5, 0xE9, 0x93,
        0xD1, 0xAD, 0xD4, 0xBB, 0xCB, 0xE3, 0xD4, 0x35, 0xC8, 0xFC, 0xEC, 0x4B, 0x39, 0x7C, 0x12, 0xA8,
        0x38, 0xA3, 0xCD, 0xA4, 0x58, 0x6B, 0xAF, 0xB0, 0x67, 0xEB, 0xE8, 0xD0, 0x10, 0xED, 0x02, 0xFE,
        0xBF, 0xF4, 0x2D, 0xF2, 0xA9, 0x49, 0xDF, 0x03, 0x0C, 0xFA, 0x4C, 0x78, 0x0C, 0x23, 0xB2, 0x34
};


// ************ MAC

//:Skein-512:   512-bit hash, msgLen =     3 bits, data = 'random+MAC'
//
//Message data:
static std::array<unsigned char, 1> tf_512h_512_3Bit_MacIn = { 0xD3 };

// MAC key =   64 bytes:
static std::array<unsigned char, 65> tf_512h_512_3Bit_MacKey = {
        0xCB, 0x41, 0xF1, 0x70, 0x6C, 0xDE, 0x09, 0x65, 0x12, 0x03, 0xC2, 0xD0, 0xEF, 0xBA, 0xDD, 0xF8,
        0x47, 0xA0, 0xD3, 0x15, 0xCB, 0x2E, 0x53, 0xFF, 0x8B, 0xAC, 0x41, 0xDA, 0x00, 0x02, 0x67, 0x2E,
        0x92, 0x02, 0x44, 0xC6, 0x6E, 0x02, 0xD5, 0xF0, 0xDA, 0xD3, 0xE9, 0x4C, 0x42, 0xBB, 0x65, 0xF0,
        0xD1, 0x41, 0x57, 0xDE, 0xCF, 0x41, 0x05, 0xEF, 0x56, 0x09, 0xD5, 0xB0, 0x98, 0x44, 0x57, 0xC1
};

// Result:
static std::array<unsigned char, 64> tf_512h_512_3Bit_MacOut = {
        0x9A, 0xB9, 0x1B, 0xBE, 0xB1, 0x56, 0x18, 0x9A, 0xAA, 0x8C, 0x26, 0x86, 0xE5, 0x07, 0x56, 0x83,
        0x86, 0xAE, 0xB6, 0x38, 0x70, 0xD6, 0x8B, 0x0A, 0x64, 0xD3, 0xC9, 0x6B, 0xC3, 0xA5, 0x10, 0x33,
        0x81, 0xA3, 0xDB, 0x2D, 0xEA, 0x47, 0xE6, 0xA1, 0xDE, 0x5B, 0x90, 0x04, 0xBC, 0x62, 0x57, 0x68,
        0x74, 0xCD, 0xAF, 0xB0, 0x5B, 0x66, 0x97, 0xE3, 0x5F, 0x53, 0xE2, 0x2E, 0x59, 0xE9, 0x0B, 0xFE
};

// :Skein-512:   512-bit hash, msgLen =     4 bits, data = 'random+MAC'

// Message data:
static std::array<unsigned char, 1> tf_512h_512_4Bit_MacIn = { 0xD3 };

// MAC key =   65 bytes:
static std::array<unsigned char, 65> tf_512h_512_4Bit_MacKey = {
        0xCB, 0x41, 0xF1, 0x70, 0x6C, 0xDE, 0x09, 0x65, 0x12, 0x03, 0xC2, 0xD0, 0xEF, 0xBA, 0xDD, 0xF8,
        0x47, 0xA0, 0xD3, 0x15, 0xCB, 0x2E, 0x53, 0xFF, 0x8B, 0xAC, 0x41, 0xDA, 0x00, 0x02, 0x67, 0x2E,
        0x92, 0x02, 0x44, 0xC6, 0x6E, 0x02, 0xD5, 0xF0, 0xDA, 0xD3, 0xE9, 0x4C, 0x42, 0xBB, 0x65, 0xF0,
        0xD1, 0x41, 0x57, 0xDE, 0xCF, 0x41, 0x05, 0xEF, 0x56, 0x09, 0xD5, 0xB0, 0x98, 0x44, 0x57, 0xC1,
        0x93
};

// Result:
static std::array<unsigned char, 64> tf_512h_512_4Bit_MacOut = {
        0xBB, 0x66, 0x8A, 0xB9, 0xEC, 0x0E, 0x7C, 0x28, 0x94, 0x78, 0x75, 0x66, 0x49, 0xBB, 0xAA, 0xC0,
        0x0A, 0xD4, 0x2F, 0xDB, 0xE2, 0x2C, 0xDE, 0x8E, 0xDD, 0xE7, 0xE0, 0x49, 0x6A, 0x02, 0xB5, 0x16,
        0x0A, 0x12, 0xFE, 0xFB, 0xBB, 0xE3, 0xF0, 0x70, 0x10, 0x04, 0x77, 0x01, 0x69, 0x42, 0x86, 0xD5,
        0x25, 0x17, 0xC8, 0x2C, 0x87, 0xEB, 0x9C, 0x0F, 0x49, 0x0F, 0x8D, 0x57, 0xDB, 0x6A, 0x9A, 0x99
};


//:Skein-512:   384-bit hash, msgLen =  1024 bits, data = 'random+MAC'
//
//Message data:
static std::array<unsigned char, 128> tf_512h_384Bit_MacIn = {
        0xD3, 0x09, 0x0C, 0x72, 0x16, 0x75, 0x17, 0xF7, 0xC7, 0xAD, 0x82, 0xA7, 0x0C, 0x2F, 0xD3, 0xF6,
        0x44, 0x3F, 0x60, 0x83, 0x01, 0x59, 0x1E, 0x59, 0x8E, 0xAD, 0xB1, 0x95, 0xE8, 0x35, 0x71, 0x35,
        0xBA, 0x26, 0xFE, 0xDE, 0x2E, 0xE1, 0x87, 0x41, 0x7F, 0x81, 0x60, 0x48, 0xD0, 0x0F, 0xC2, 0x35,
        0x12, 0x73, 0x7A, 0x21, 0x13, 0x70, 0x9A, 0x77, 0xE4, 0x17, 0x0C, 0x49, 0xA9, 0x4B, 0x7F, 0xDF,
        0xF4, 0x5F, 0xF5, 0x79, 0xA7, 0x22, 0x87, 0x74, 0x31, 0x02, 0xE7, 0x76, 0x6C, 0x35, 0xCA, 0x5A,
        0xBC, 0x5D, 0xFE, 0x2F, 0x63, 0xA1, 0xE7, 0x26, 0xCE, 0x5F, 0xBD, 0x29, 0x26, 0xDB, 0x03, 0xA2,
        0xDD, 0x18, 0xB0, 0x3F, 0xC1, 0x50, 0x8A, 0x9A, 0xAC, 0x45, 0xEB, 0x36, 0x24, 0x40, 0x20, 0x3A,
        0x32, 0x3E, 0x09, 0xED, 0xEE, 0x63, 0x24, 0xEE, 0x2E, 0x37, 0xB4, 0x43, 0x2C, 0x18, 0x67, 0xED
};

// MAC key =   32 bytes:
static std::array<unsigned char, 32> tf_512h_384Bit_MacKey = {
        0xCB, 0x41, 0xF1, 0x70, 0x6C, 0xDE, 0x09, 0x65, 0x12, 0x03, 0xC2, 0xD0, 0xEF, 0xBA, 0xDD, 0xF8,
        0x47, 0xA0, 0xD3, 0x15, 0xCB, 0x2E, 0x53, 0xFF, 0x8B, 0xAC, 0x41, 0xDA, 0x00, 0x02, 0x67, 0x2E
};

// Result:
static std::array<unsigned char, 48> tf_512h_384Bit_MacOut = {
        0xDF, 0xBF, 0x5C, 0x13, 0x19, 0xA1, 0xD9, 0xD7, 0x0E, 0xFB, 0x2F, 0x16, 0x00, 0xFB, 0xCF, 0x69,
        0x4F, 0x93, 0x59, 0x07, 0xF3, 0x1D, 0x24, 0xA1, 0x6D, 0x6C, 0xD2, 0xFB, 0x2D, 0x78, 0x55, 0xA7,
        0x69, 0x68, 0x17, 0x66, 0xC0, 0xA2, 0x9D, 0xA7, 0x78, 0xEE, 0xD3, 0x46, 0xCD, 0x1D, 0x74, 0x0F
};

//:Skein-512:   512-bit hash, msgLen =  1024 bits, data = 'random+MAC'
//
//Message data:
static std::array<unsigned char, 128> tf_512h_512Bit_MacIn = {
        0xD3, 0x09, 0x0C, 0x72, 0x16, 0x75, 0x17, 0xF7, 0xC7, 0xAD, 0x82, 0xA7, 0x0C, 0x2F, 0xD3, 0xF6,
        0x44, 0x3F, 0x60, 0x83, 0x01, 0x59, 0x1E, 0x59, 0x8E, 0xAD, 0xB1, 0x95, 0xE8, 0x35, 0x71, 0x35,
        0xBA, 0x26, 0xFE, 0xDE, 0x2E, 0xE1, 0x87, 0x41, 0x7F, 0x81, 0x60, 0x48, 0xD0, 0x0F, 0xC2, 0x35,
        0x12, 0x73, 0x7A, 0x21, 0x13, 0x70, 0x9A, 0x77, 0xE4, 0x17, 0x0C, 0x49, 0xA9, 0x4B, 0x7F, 0xDF,
        0xF4, 0x5F, 0xF5, 0x79, 0xA7, 0x22, 0x87, 0x74, 0x31, 0x02, 0xE7, 0x76, 0x6C, 0x35, 0xCA, 0x5A,
        0xBC, 0x5D, 0xFE, 0x2F, 0x63, 0xA1, 0xE7, 0x26, 0xCE, 0x5F, 0xBD, 0x29, 0x26, 0xDB, 0x03, 0xA2,
        0xDD, 0x18, 0xB0, 0x3F, 0xC1, 0x50, 0x8A, 0x9A, 0xAC, 0x45, 0xEB, 0x36, 0x24, 0x40, 0x20, 0x3A,
        0x32, 0x3E, 0x09, 0xED, 0xEE, 0x63, 0x24, 0xEE, 0x2E, 0x37, 0xB4, 0x43, 0x2C, 0x18, 0x67, 0xED
};

//        MAC key =   64 bytes:
static std::array<unsigned char, 64> tf_512h_512Bit_MacKey = {
        0xCB, 0x41, 0xF1, 0x70, 0x6C, 0xDE, 0x09, 0x65, 0x12, 0x03, 0xC2, 0xD0, 0xEF, 0xBA, 0xDD, 0xF8,
        0x47, 0xA0, 0xD3, 0x15, 0xCB, 0x2E, 0x53, 0xFF, 0x8B, 0xAC, 0x41, 0xDA, 0x00, 0x02, 0x67, 0x2E,
        0x92, 0x02, 0x44, 0xC6, 0x6E, 0x02, 0xD5, 0xF0, 0xDA, 0xD3, 0xE9, 0x4C, 0x42, 0xBB, 0x65, 0xF0,
        0xD1, 0x41, 0x57, 0xDE, 0xCF, 0x41, 0x05, 0xEF, 0x56, 0x09, 0xD5, 0xB0, 0x98, 0x44, 0x57, 0xC1
};

//        Result:
static std::array<unsigned char, 64> tf_512h_512Bit_MacOut = {
        0x04, 0xD8, 0xCD, 0xDB, 0x0A, 0xD9, 0x31, 0xD5, 0x4D, 0x19, 0x58, 0x99, 0xA0, 0x94, 0x68, 0x43,
        0x44, 0xE9, 0x02, 0x28, 0x60, 0x37, 0x27, 0x28, 0x90, 0xBC, 0xE9, 0x8A, 0x41, 0x81, 0x3E, 0xDC,
        0x37, 0xA3, 0xCE, 0xE1, 0x90, 0xA6, 0x93, 0xFC, 0xCA, 0x61, 0x3E, 0xE3, 0x00, 0x49, 0xCE, 0x7E,
        0xC2, 0xBD, 0xFF, 0x96, 0x13, 0xF5, 0x67, 0x78, 0xA1, 0x3F, 0x8C, 0x28, 0xA2, 0x1D, 0x16, 0x7A
};

using namespace std;

class BotanSkeinTestFixture: public ::testing::Test {
public:
    BotanSkeinTestFixture() = default;

    BotanSkeinTestFixture(const BotanSkeinTestFixture& other) = delete;
    BotanSkeinTestFixture(const BotanSkeinTestFixture&& other) = delete;
    BotanSkeinTestFixture& operator= (const BotanSkeinTestFixture& other) = delete;
    BotanSkeinTestFixture& operator= (const BotanSkeinTestFixture&& other) = delete;

    void SetUp() override {
        // code here will execute just before the test ensues
        LOGGER_INSTANCE setLogLevel(DEBUGGING);
    }

    void TearDown( ) override {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
    }

    ~BotanSkeinTestFixture( ) override {
        // cleanup any pending stuff, but no exceptions allowed
        LOGGER_INSTANCE setLogLevel(VERBOSE);
    }
};

TEST_F(BotanSkeinTestFixture, LongHashes_1024) {
    std::unique_ptr<Botan::HashFunction> hashZeros(Botan::HashFunction::create_or_throw("Skein-512(1024)"));
    hashZeros->update(reinterpret_cast<const uint8_t *>(tf_1024h_0_In.data()), tf_1024h_0_In.size());
    auto botanHashZeros = hashZeros->final();

    ASSERT_EQ(128, botanHashZeros.size());
    ASSERT_EQ(0, memcmp(tf_1024h_0_Out.data(), botanHashZeros.data(), tf_1024h_0_Out.size()));

    std::unique_ptr<Botan::HashFunction> hashData(Botan::HashFunction::create_or_throw("Skein-512(1024)"));
    hashData->update(reinterpret_cast<const uint8_t *>(tf_1024h_D_In.data()), tf_1024h_D_In.size());
    auto botanHashData = hashData->final();

    ASSERT_EQ(128, botanHashData.size());
    ASSERT_EQ(0, memcmp(tf_1024h_D_Out.data(), botanHashData.data(), tf_1024h_D_Out.size()));
}

TEST_F(BotanSkeinTestFixture, LongHashes_520) {
    std::unique_ptr<Botan::HashFunction> hashZeros(Botan::HashFunction::create_or_throw("Skein-512(520)"));
    hashZeros->update(reinterpret_cast<const uint8_t *>(tf_520h_0_In.data()), tf_520h_0_In.size());
    auto botanHashZeros = hashZeros->final();

    ASSERT_EQ(65, botanHashZeros.size());
    ASSERT_EQ(0, memcmp(tf_520h_0_Out.data(), botanHashZeros.data(), tf_520h_0_Out.size()));

    std::unique_ptr<Botan::HashFunction> hashData(Botan::HashFunction::create_or_throw("Skein-512(520)"));
    hashData->update(reinterpret_cast<const uint8_t *>(tf_520h_D_In.data()), tf_520h_D_In.size());
    auto botanHashData = hashData->final();

    ASSERT_EQ(65, botanHashData.size());
    ASSERT_EQ(0, memcmp(tf_520h_D_Out.data(), botanHashData.data(), tf_520h_D_Out.size()));
}

TEST_F(BotanSkeinTestFixture, LongHashes_1032) {
    std::unique_ptr<Botan::HashFunction> hashZeros(Botan::HashFunction::create_or_throw("Skein-512(1032)"));
    hashZeros->update(reinterpret_cast<const uint8_t *>(tf_1032h_0_In.data()), tf_1032h_0_In.size());
    auto botanHashZeros = hashZeros->final();

    ASSERT_EQ(129, botanHashZeros.size());
    ASSERT_EQ(0, memcmp(tf_1032h_0_Out.data(), botanHashZeros.data(), tf_1032h_0_Out.size()));

    std::unique_ptr<Botan::HashFunction> hashData(Botan::HashFunction::create_or_throw("Skein-512(1032)"));
    hashData->update(reinterpret_cast<const uint8_t *>(tf_1032h_D_In.data()), tf_1032h_D_In.size());
    auto botanHashData = hashData->final();

    ASSERT_EQ(129, botanHashData.size());
    ASSERT_EQ(0, memcmp(tf_1032h_D_Out.data(), botanHashData.data(), tf_1032h_D_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_1Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_1Bit_In.data(), 1);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_1Bit_Out.data(), botanHash.data(), tf_512h_1Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_2Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_2Bit_In.data(), 2);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_2Bit_Out.data(), botanHash.data(), tf_512h_2Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_3Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_3Bit_In.data(), 3);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_3Bit_Out.data(), botanHash.data(), tf_512h_3Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_4Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_4Bit_In.data(), 4);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_4Bit_Out.data(), botanHash.data(), tf_512h_4Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_5Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_5Bit_In.data(), 5);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_5Bit_Out.data(), botanHash.data(), tf_512h_5Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_7Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_7Bit_In.data(), 7);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_7Bit_Out.data(), botanHash.data(), tf_512h_7Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_8Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_8Bit_In.data(), 8);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_8Bit_Out.data(), botanHash.data(), tf_512h_8Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_9Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_9Bit_In.data(), 9);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_9Bit_Out.data(), botanHash.data(), tf_512h_9Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_512Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_512Bit_In.data(), 512);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_512Bit_Out.data(), botanHash.data(), tf_512h_512Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Partial_513Bit) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->add_data_bits(tf_512h_513Bit_In.data(), 513);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_513Bit_Out.data(), botanHash.data(), tf_512h_513Bit_Out.size()));
}

TEST_F(BotanSkeinTestFixture, Mac_384) {
    auto hash(new Botan::Skein_512(384, "" ));
    hash->setMacKey(tf_512h_384Bit_MacKey.data(), 32);
    hash->update(tf_512h_384Bit_MacIn.data(), 128);
    auto botanHash = hash->final();
    ASSERT_EQ(48, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_384Bit_MacOut.data(), botanHash.data(), tf_512h_384Bit_MacOut.size()));
}

TEST_F(BotanSkeinTestFixture, Mac_512) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->setMacKey(tf_512h_512Bit_MacKey.data(), 64);
    hash->update(tf_512h_512Bit_MacIn.data(), 128);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_512Bit_MacOut.data(), botanHash.data(), tf_512h_512Bit_MacOut.size()));
}

TEST_F(BotanSkeinTestFixture, Mac_512_3) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->setMacKey(tf_512h_512_3Bit_MacKey.data(), 64);
    hash->add_data_bits(tf_512h_512_3Bit_MacIn.data(), 3);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_512_3Bit_MacOut.data(), botanHash.data(), tf_512h_512_3Bit_MacOut.size()));
}

TEST_F(BotanSkeinTestFixture, Mac_512_4) {
    auto hash(new Botan::Skein_512(512, "" ));
    hash->setMacKey(tf_512h_512_4Bit_MacKey.data(), 65);
    hash->add_data_bits(tf_512h_512_4Bit_MacIn.data(), 4);
    auto botanHash = hash->final();
    ASSERT_EQ(64, botanHash.size());
    ASSERT_EQ(0, memcmp(tf_512h_512_4Bit_MacOut.data(), botanHash.data(), tf_512h_512_4Bit_MacOut.size()));
}
