#include "GLfunc.h"

template<typename Type>
class VAP {
public:
        VAP(uint size, GLenum GLtype) : size(size), GLtype(GLtype);

        uint size;
        Type dataType = new Type();
        GLenum GLtype;

        ~VAP() { delete dataType; }
};

template<typename Type> 
void genVertexAttrib(GLuint &VAO, GLuint &VBO, uint* sizeofBuffer, GLenum glTypeDraw, VAP<Type> vap01, 
uint secondGroup, uint thirdGroup, Type dataType) {
        
        uint totalDataLenght = firstGroup + secondGroup + thirdGroup;
        
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(sizeofBuffer), sizeofBuffer, glTypeDraw);

        glVertexAttribPointer(0, firstGroup, GL_FLOAT, GL_FALSE, totalDataLenght * sizeof(dataType), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, secondGroup, GL_FLOAT, GL_FALSE, totalDataLenght * sizeof(dataType), (void*)(firstGroup * sizeof(dataType)));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, thirdGroup, GL_FLOAT, GL_FALSE, totalDataLenght * sizeof(dataType), (void*)((firstGroup + secondGroup) * sizeof(dataType)));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0); 

}