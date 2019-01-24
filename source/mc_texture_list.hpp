// mc_texture_list.hpp
/////////////////////////////////////////////////////////////////////////


#include <string>
#include <vector>


enum class TextureType { BACKGROUND, BUTTON, SPINNER, EXTRA_SPINNER, NONE };


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
    { "pattern3.jpg", 3, TextureType::EXTRA_SPINNER },
    { "pattern5.jpg", 5, TextureType::EXTRA_SPINNER },
    { "pattern6.jpg", 6, TextureType::EXTRA_SPINNER },
    { "pattern7.jpg", 7, TextureType::EXTRA_SPINNER },
    { "pattern8.jpg", 8, TextureType::EXTRA_SPINNER },
    { "pattern9.jpg", 9, TextureType::EXTRA_SPINNER },
    { "patterna.jpg", 10, TextureType::EXTRA_SPINNER },
    { "patternb.jpg", 11, TextureType::EXTRA_SPINNER },
    { "patternc.jpg", 12, TextureType::EXTRA_SPINNER },
    { "patternf.jpg", 15, TextureType::EXTRA_SPINNER },
    { "patterng.jpg", 16, TextureType::EXTRA_SPINNER },
    { "patternh.jpg", 17, TextureType::EXTRA_SPINNER },
    { "patterni.jpg", 18, TextureType::EXTRA_SPINNER },
    { "patternn.jpg", 23, TextureType::EXTRA_SPINNER },
    { "patterno.jpg", 24, TextureType::EXTRA_SPINNER },
    { "patternr.jpg", 27, TextureType::EXTRA_SPINNER },
    { "patternw.jpg", 32, TextureType::EXTRA_SPINNER },
    { "patterny.jpg", 34, TextureType::EXTRA_SPINNER },
    { "patternz.jpg", 35 , TextureType::EXTRA_SPINNER },
    { "pattern0a.jpg", 89, TextureType::EXTRA_SPINNER },
    { "pattern0b.jpg", 90, TextureType::EXTRA_SPINNER },
    { "pattern0c.jpg", 91, TextureType::EXTRA_SPINNER },
    { "pattern0d.jpg", 92, TextureType::EXTRA_SPINNER },
    { "pattern0e.jpg", 93, TextureType::EXTRA_SPINNER },
    { "pattern0f.jpg", 94, TextureType::EXTRA_SPINNER },
    { "pattern0g.jpg", 95, TextureType::EXTRA_SPINNER },
    { "pattern0h.jpg", 96, TextureType::EXTRA_SPINNER },
    { "pattern0i.jpg", 97, TextureType::EXTRA_SPINNER },
    { "pattern0j.jpg", 98, TextureType::EXTRA_SPINNER },
    { "pattern0k.jpg", 99, TextureType::EXTRA_SPINNER },
    { "pattern0l.jpg", 100, TextureType::EXTRA_SPINNER },
    { "patternzb.jpg", 101, TextureType::EXTRA_SPINNER },
    { "patternzd.jpg", 102, TextureType::EXTRA_SPINNER },
    { "patternze.jpg", 103, TextureType::EXTRA_SPINNER },
    { "patternzk.jpg", 104, TextureType::EXTRA_SPINNER },
    { "patternzn.jpg", 105, TextureType::EXTRA_SPINNER },
    { "patternzp.jpg", 106, TextureType::EXTRA_SPINNER },
    { "patternzq.jpg", 107 , TextureType::EXTRA_SPINNER },
    { "quilta.jpg", 108, TextureType::EXTRA_SPINNER },
    { "quiltb.jpg", 109, TextureType::EXTRA_SPINNER },
    { "quiltc.jpg", 110, TextureType::EXTRA_SPINNER },
    { "quiltd.jpg", 111, TextureType::EXTRA_SPINNER },
    { "quilte.jpg", 112, TextureType::EXTRA_SPINNER },
    { "quiltf.jpg", 113, TextureType::EXTRA_SPINNER },
    { "quiltg.jpg", 59, TextureType::EXTRA_SPINNER },
    { "quilth.jpg", 60, TextureType::EXTRA_SPINNER },
    { "quilti.jpg", 61, TextureType::EXTRA_SPINNER },
    { "quiltj.jpg", 62, TextureType::EXTRA_SPINNER },
    { "quiltk.jpg", 63, TextureType::EXTRA_SPINNER },
    { "quiltl.jpg", 64, TextureType::EXTRA_SPINNER },
    { "quiltm.jpg", 65, TextureType::EXTRA_SPINNER },
    { "quiltn.jpg", 66, TextureType::EXTRA_SPINNER },
    { "quilto.jpg", 67, TextureType::EXTRA_SPINNER },
    { "quiltp.jpg", 68, TextureType::EXTRA_SPINNER },
    { "quiltq.jpg", 69, TextureType::EXTRA_SPINNER },
    { "quiltr.jpg", 70, TextureType::EXTRA_SPINNER },
    { "quilts.jpg", 71, TextureType::EXTRA_SPINNER },
    { "quiltt.jpg", 72, TextureType::EXTRA_SPINNER },
    { "quiltu.jpg", 73, TextureType::EXTRA_SPINNER },
    { "quiltv.jpg", 74, TextureType::EXTRA_SPINNER },
    { "", 0, TextureType::NONE }
};






// */
