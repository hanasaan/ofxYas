//
//  Created by Yuya Hanai, https://github.com/hanasaan/
//
#pragma once

#include "ofBaseTypes.h"

#include <yas/mem_streams.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/std_types.hpp>

namespace yas
{
    // conversion functions for of base types
    template<typename Ar>
    void serialize(Ar &ar, ofVec2f & m) {
        ar & m.x & m.y;
    }

    template<typename Ar>
    void serialize(Ar &ar, ofVec3f & m) {
        ar & m.x & m.y & m.z;
    }
    
    template<typename Ar>
    void serialize(Ar &ar, ofVec4f & m) {
        ar & m.x & m.y & m.z & m.w;
    }
    
    template<typename Ar, class T>
    void serialize(Ar &ar, ofColor_<T> & m) {
        ar & m.r & m.g & m.b & m.a;
    }
    
    template<typename Ar>
    void serialize(Ar &ar, ofQuaternion & m) {
        ar & m._v;
    }
    
    template<typename Ar>
    void serialize(Ar &ar, ofRectangle & m) {
        ar & m.x & m.y & m.width & m.height;
    }
    
    template<typename Ar>
    void serialize(Ar &ar, ofMatrix4x4 & m) {
        ar & m._mat;
    }
    
    // main func
    template<bool compact = false, typename T>
    void serialize(const T& obj, ofBuffer& b)
    {
        yas::mem_ostream os;
        const std::size_t f = yas::binary|yas::no_header|yas::ehost|(compact ? yas::compacted : 0);
        yas::binary_oarchive<yas::mem_ostream, f> oa(os);
        oa & obj;
        auto ptr = os.get_intrusive_buffer();
        b = ofBuffer(ptr.data, ptr.size);
        return b;
    }

    template<bool compact = false, typename T>
    void deserialize(T& obj, const ofBuffer& b)
    {
        yas::mem_istream is(b.getData(), b.size());
        const std::size_t f = yas::binary|yas::no_header|yas::ehost|(compact ? yas::compacted : 0);
        yas::binary_iarchive<yas::mem_istream, f> ia(is);
        ia & obj;
    }
    
    template<typename T>
    void serializeCompacted(const T& obj, ofBuffer& b)
    {
        serialize<true, T>(obj, b);
    }
    
    template<typename T>
    void deserializeCompacted(T& obj, const ofBuffer& b)
    {
        deserialize<true, T>(obj, b);
    }

}

// from http://fimbul.hateblo.jp/entry/2014/10/10/235727
#define CAT_I(x, y) x ## y
#define CAT(x, y) CAT_I(x, y)

#define INC0 1
#define INC1 2
#define INC2 3
#define INC3 4
#define INC4 5
#define INC5 6
#define INC6 7
#define INC7 8
#define INC8 9
#define INC(i) CAT(INC, i)

#define EMPTY(...)
#define DEF_COMMA0 _,1 EMPTY
#define COMMA0() ,0
#define IS_EMPTY_III(f, s) s
#define IS_EMPTY_II(t) IS_EMPTY_III t
#define IS_EMPTY_I(x) IS_EMPTY_II((DEF_ ## x()))
#define IS_EMPTY(x, ...) IS_EMPTY_I(x COMMA0)

#define IF_0(x, y) y
#define IF_1(x, y) x
#define IF(cond, x, y) CAT(IF_, cond)(x, y)

#define FOR_EACH_I9(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I8(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I7(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I6(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I5(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I4(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I3(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I2(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I1(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I0(i, F, x, ...) F(x) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH_I(i, F, ...) IF(IS_EMPTY(__VA_ARGS__), EMPTY, CAT(FOR_EACH_I, i))(INC(i), F, __VA_ARGS__)
#define FOR_EACH(F, ...) FOR_EACH_I(0, F, __VA_ARGS__)

#define CAT_AND(x) &x
#define OFX_YAS_CONCAT(...) FOR_EACH(CAT_AND, __VA_ARGS__)

#define OFX_YAS_DEFINE(...) \
public:\
template<typename Ar> \
void serialize(Ar &ar) {ar OFX_YAS_CONCAT(__VA_ARGS__);}

namespace ofxYas = yas;
