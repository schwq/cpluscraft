#include "BlockCollision.h"

void checkOverLapFaces() {

    for(uint blocks = 0; blocks < gl_Blocks.size(); blocks++) {
        for(uint faces = 0; faces < 6; faces++) {
            for(uint blockToCompare = 0; blockToCompare < gl_Blocks.size(); blockToCompare++) {
                if(blockToCompare == blocks) continue;
                for(uint fragments = 0; fragments < 12; fragments++) {
                    if(glm::translate(gl_Blocks.at(blocks).getModelMatrixPos(), gl_Blocks.at(blocks).fragments.at(fragments).vc1) == 
                    glm::translate(gl_Blocks.at(blockToCompare).getModelMatrixPos(),gl_Blocks.at(blockToCompare).fragments.at(fragments).vc1) &&
                    glm::translate(gl_Blocks.at(blocks).getModelMatrixPos(), gl_Blocks.at(blocks).fragments.at(fragments).vc2) == 
                    glm::translate(gl_Blocks.at(blockToCompare).getModelMatrixPos(),gl_Blocks.at(blockToCompare).fragments.at(fragments).vc2)  &&
                    glm::translate(gl_Blocks.at(blocks).getModelMatrixPos(), gl_Blocks.at(blocks).fragments.at(fragments).vc3) == 
                    glm::translate(gl_Blocks.at(blockToCompare).getModelMatrixPos(),gl_Blocks.at(blockToCompare).fragments.at(fragments).vc3) ) {
                        gl_Blocks.at(blocks).acessFaceOrientation(gl_Blocks.at(blocks).fragments.at(fragments).orientation).setShouldDraw(false);
                    } else {
                        gl_Blocks.at(blocks).acessFaceOrientation(gl_Blocks.at(blocks).fragments.at(fragments).orientation).setShouldDraw(true);
                    }
                }
            }
        }
    }
}