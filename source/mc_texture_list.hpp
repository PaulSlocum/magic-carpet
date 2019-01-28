// mc_texture_list.hpp
/////////////////////////////////////////////////////////////////////////


#include <string>


enum class TextureType { BACKGROUND, BUTTON, SPINNER, UNUSED, NONE };


struct TextureDef
{
    std::string filename;
    int textureSlot;
    TextureType type;
};


// NOTE: LIST SHOULD END WITH AN EMPTY FILENAME AND TextureType::NONE
const TextureDef TEXTURE_LOAD_LIST[] =
{ 
    { "menuBG2c.jpg", 200, TextureType::BACKGROUND },
    { "menuBG2d.jpg", 201, TextureType::BACKGROUND },
    { "bnChalice.jpg", 300, TextureType::BUTTON }, 
    { "bnGrid.jpg", 301, TextureType::BUTTON }, 
    { "bnBird.jpg", 302, TextureType::BUTTON }, 
    { "pattern0.jpg", 0, TextureType::SPINNER },
    { "pattern1.jpg", 1, TextureType::SPINNER },
    { "pattern2.jpg", 2, TextureType::SPINNER },
    { "pattern4.jpg", 4, TextureType::SPINNER },
    { "patternd.jpg", 13, TextureType::SPINNER },
    { "patterne.jpg", 14, TextureType::SPINNER },
    { "patternj.jpg", 19, TextureType::SPINNER },
    { "patternk.jpg", 20, TextureType::SPINNER },
    { "patternl.jpg", 21, TextureType::SPINNER },
    { "patternm.jpg", 22, TextureType::SPINNER },
    { "patternp.jpg", 25, TextureType::SPINNER },
    { "patternq_dark.jpg", 26, TextureType::SPINNER },
    { "patterns.jpg", 28, TextureType::SPINNER },
    { "patternt.jpg", 29, TextureType::SPINNER },
    { "patternu.jpg", 30, TextureType::SPINNER },
    { "patternv.jpg", 31, TextureType::SPINNER },
    { "patternx.jpg", 33, TextureType::SPINNER },
    { "pattern_black.jpg", 53, TextureType::SPINNER },
    { "pattern_white.jpg", 54, TextureType::SPINNER },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "pattern_blue.jpg", 55, TextureType::SPINNER },
    { "pattern_red.jpg", 56, TextureType::SPINNER },
    { "pattern_beige.jpg", 57, TextureType::SPINNER },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "patternza.jpg", 36, TextureType::SPINNER },
    { "patternzc.jpg", 38, TextureType::SPINNER },
    { "patternzf.jpg", 41, TextureType::SPINNER },  // <-- ISSUE LOADING WITH ujpeg (FIXED, THIS NOTE CAN PROBABLY BE REMOVED)
    { "patternzg.jpg", 42, TextureType::SPINNER },
    { "patternzh.jpg", 43, TextureType::SPINNER },
    { "patternzi.jpg", 44, TextureType::SPINNER },
    { "patternzj.jpg", 45, TextureType::SPINNER },
    { "patternzk.jpg", 46, TextureType::SPINNER },
    { "patternzl.jpg", 47, TextureType::SPINNER },
    { "patternzm.jpg", 48, TextureType::SPINNER },
    { "patternzn.jpg", 49, TextureType::SPINNER },
    { "patternzo.jpg", 50, TextureType::SPINNER },
    { "patternzq.jpg", 107, TextureType::SPINNER },
    { "quiltl.jpg", 64, TextureType::SPINNER },
    { "quiltv.jpg", 74, TextureType::SPINNER },
    { "pattern0e.jpg", 93, TextureType::SPINNER },
    { "pattern0h.jpg", 96, TextureType::SPINNER },
    { "pattern0i.jpg", 97, TextureType::SPINNER },
    { "quiltd.jpg", 111, TextureType::SPINNER },
    /////////////////////////////////////////////////////////////
    { "pattern3.jpg", 3, TextureType::UNUSED },
    { "pattern5.jpg", 5, TextureType::UNUSED },
    { "pattern6.jpg", 6, TextureType::UNUSED },
    { "pattern7.jpg", 7, TextureType::UNUSED },
    { "pattern8.jpg", 8, TextureType::UNUSED },
    { "pattern9.jpg", 9, TextureType::UNUSED },
    { "patterna.jpg", 10, TextureType::UNUSED },
    { "patternb.jpg", 11, TextureType::UNUSED },
    { "patternc.jpg", 12, TextureType::UNUSED },
    { "patternf.jpg", 15, TextureType::UNUSED },
    { "patterng.jpg", 16, TextureType::UNUSED },
    { "patternh.jpg", 17, TextureType::UNUSED },
    { "patterni.jpg", 18, TextureType::UNUSED },
    { "patternn.jpg", 23, TextureType::UNUSED },
    { "patterno.jpg", 24, TextureType::UNUSED },
    { "patternr.jpg", 27, TextureType::UNUSED },
    { "patternw.jpg", 32, TextureType::UNUSED },
    { "patterny.jpg", 34, TextureType::UNUSED },
    { "patternz.jpg", 35 , TextureType::UNUSED },
    { "pattern0a.jpg", 89, TextureType::UNUSED },
    { "pattern0b.jpg", 90, TextureType::UNUSED },
    { "pattern0c.jpg", 91, TextureType::UNUSED },
    { "pattern0d.jpg", 92, TextureType::UNUSED },
    { "pattern0e.jpg", 93, TextureType::UNUSED },
    { "pattern0f.jpg", 94, TextureType::UNUSED },
    { "pattern0g.jpg", 95, TextureType::UNUSED },
    { "pattern0h.jpg", 96, TextureType::UNUSED },
    { "pattern0i.jpg", 97, TextureType::UNUSED },
    { "pattern0j.jpg", 98, TextureType::UNUSED },
    { "pattern0k.jpg", 99, TextureType::UNUSED },
    { "pattern0l.jpg", 100, TextureType::UNUSED },
    { "patternzb.jpg", 101, TextureType::UNUSED },
    { "patternzd.jpg", 102, TextureType::UNUSED },
    { "patternze.jpg", 103, TextureType::UNUSED },
    { "patternzk.jpg", 104, TextureType::UNUSED },
    { "patternzn.jpg", 105, TextureType::UNUSED },
    { "patternzp.jpg", 106, TextureType::UNUSED },
    { "patternzq.jpg", 107 , TextureType::UNUSED },
    { "quilta.jpg", 108, TextureType::UNUSED },
    { "quiltb.jpg", 109, TextureType::UNUSED },
    { "quiltc.jpg", 110, TextureType::UNUSED },
    { "quiltd.jpg", 111, TextureType::UNUSED },
    { "quilte.jpg", 112, TextureType::UNUSED },
    { "quiltf.jpg", 113, TextureType::UNUSED },
    { "quiltg.jpg", 59, TextureType::UNUSED },
    { "quilth.jpg", 60, TextureType::UNUSED },
    { "quilti.jpg", 61, TextureType::UNUSED },
    { "quiltj.jpg", 62, TextureType::UNUSED },
    { "quiltk.jpg", 63, TextureType::UNUSED },
    { "quiltl.jpg", 64, TextureType::UNUSED },
    { "quiltm.jpg", 65, TextureType::UNUSED },
    { "quiltn.jpg", 66, TextureType::UNUSED },
    { "quilto.jpg", 67, TextureType::UNUSED },
    { "quiltp.jpg", 68, TextureType::UNUSED },
    { "quiltq.jpg", 69, TextureType::UNUSED },
    { "quiltr.jpg", 70, TextureType::UNUSED },
    { "quilts.jpg", 71, TextureType::UNUSED },
    { "quiltt.jpg", 72, TextureType::UNUSED },
    { "quiltu.jpg", 73, TextureType::UNUSED },
    { "quiltv.jpg", 74, TextureType::UNUSED },
    { "", 0, TextureType::NONE }
};




