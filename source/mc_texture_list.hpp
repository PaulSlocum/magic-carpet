// mc_texture_list.hpp
/////////////////////////////////////////////////////////////////////////


#include <string>


struct TextureDef
{
    std::string filename;
    int textureSlot;
    bool isUsed;
};


const int TEXTURE_LOAD_LIST_LENGTH = 99;
const TextureDef TEXTURE_LOAD_LIST[] = 
{ 
    { "pattern0.jpg", 0, true },
    { "pattern1.jpg", 1, true },
    { "pattern2.jpg", 2, true },
    { "pattern4.jpg", 4, true },
    { "patternd.jpg", 13, true },
    { "patterne.jpg", 14, true },
    { "patternj.jpg", 19, true },
    { "patternk.jpg", 20, true },
    { "patternl.jpg", 21, true },
    { "patternm.jpg", 22, true },
    { "patternp.jpg", 25, true },
    { "patternq_dark.jpg", 26, true },
    { "patterns.jpg", 28, true },
    { "patternt.jpg", 29, true },
    { "patternu.jpg", 30, true },
    { "patternv.jpg", 31, true },
    { "patternx.jpg", 33, true },
    { "pattern_black.jpg", 53, true },
    { "pattern_white.jpg", 54, true },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "pattern_blue.jpg", 55, true },
    { "pattern_red.jpg", 56, true },
    { "pattern_beige.jpg", 57, true },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "patternza.jpg", 36, true },
    { "patternzc.jpg", 38, true },
    { "patternzf.jpg", 41, true },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "patternzg.jpg", 42, true },
    { "patternzh.jpg", 43, true },
    { "patternzi.jpg", 44, true },
    { "patternzj.jpg", 45, true },
    { "patternzk.jpg", 46, true },
    { "patternzl.jpg", 47, true },
    { "patternzm.jpg", 48, true },
    { "patternzn.jpg", 49, true },
    { "patternzo.jpg", 50, true },
    { "patternzq.jpg", 107, true },
    { "quiltl.jpg", 64, true },
    { "quiltv.jpg", 74, true },
    { "pattern0e.jpg", 93, true },
    { "pattern0h.jpg", 96, true },
    { "pattern0i.jpg", 97, true },
    { "quiltd.jpg", 111, true },
    /////////////////////////////////////////////////////////////
    { "pattern3.jpg", 3, false },
    { "pattern5.jpg", 5, false },
    { "pattern6.jpg", 6, false },
    { "pattern7.jpg", 7, false },
    { "pattern8.jpg", 8, false },
    { "pattern9.jpg", 9, false },
    { "patterna.jpg", 10, false },
    { "patternb.jpg", 11, false },
    { "patternc.jpg", 12, false },
    { "patternf.jpg", 15, false },
    { "patterng.jpg", 16, false },
    { "patternh.jpg", 17, false },
    { "patterni.jpg", 18, false },
    { "patternn.jpg", 23, false },
    { "patterno.jpg", 24, false },
    { "patternr.jpg", 27, false },
    { "patternw.jpg", 32, false },
    { "patterny.jpg", 34, false },
    { "patternz.jpg", 35 , false },
    { "pattern0a.jpg", 89, false },
    { "pattern0b.jpg", 90, false },
    { "pattern0c.jpg", 91, false },
    { "pattern0d.jpg", 92, false },
    { "pattern0e.jpg", 93, false },
    { "pattern0f.jpg", 94, false },
    { "pattern0g.jpg", 95, false },
    { "pattern0h.jpg", 96, false },
    { "pattern0i.jpg", 97, false },
    { "pattern0j.jpg", 98, false },
    { "pattern0k.jpg", 99, false },
    { "pattern0l.jpg", 100, false },
    { "patternzb.jpg", 101, false },
    { "patternzd.jpg", 102, false },
    { "patternze.jpg", 103, false },
    { "patternzk.jpg", 104, false },
    { "patternzn.jpg", 105, false },
    { "patternzp.jpg", 106, false },
    { "patternzq.jpg", 107 , false },
    { "quilta.jpg", 108, false },
    { "quiltb.jpg", 109, false },
    { "quiltc.jpg", 110, false },
    { "quiltd.jpg", 111, false },
    { "quilte.jpg", 112, false },
    { "quiltf.jpg", 113, false },
    { "quiltg.jpg", 59, false },
    { "quilth.jpg", 60, false },
    { "quilti.jpg", 61, false },
    { "quiltj.jpg", 62, false },
    { "quiltk.jpg", 63, false },
    { "quiltl.jpg", 64, false },
    { "quiltm.jpg", 65, false },
    { "quiltn.jpg", 66, false },
    { "quilto.jpg", 67, false },
    { "quiltp.jpg", 68, false },
    { "quiltq.jpg", 69, false },
    { "quiltr.jpg", 70, false },
    { "quilts.jpg", 71, false },
    { "quiltt.jpg", 72, false },
    { "quiltu.jpg", 73, false },
    { "quiltv.jpg", 74, false },
};






// */
