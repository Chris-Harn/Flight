#include "OpenGL/Texture.h"

#include <GL/glew.h>

Texture::Texture()
    : m_textureID( 0 ), m_width( 0 ), m_height( 0 ), m_internalFormat( GL_RED ),
    m_imageFormat( GL_RED ), m_wrapS( GL_CLAMP_TO_EDGE ), m_wrapT( GL_CLAMP_TO_EDGE ), m_filterMin( GL_LINEAR ),
    m_filterMax( GL_LINEAR ) {

}

Texture::~Texture() {
    // Never clear OpenGL resources in deconstructor
}

void Texture::Generate( unsigned int width, unsigned int height, float *data ) {
    m_width = width;
    m_height = height;
    glBindTexture( GL_TEXTURE_2D, m_textureID );
    glTexImage2D( GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_imageFormat, GL_FLOAT, data );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::Bind( unsigned int slot ) const {
    glActiveTexture( GL_TEXTURE0 + slot );
    glBindTexture( GL_TEXTURE_2D, this->m_textureID );
}

void Texture::Clean() {
    if( m_textureID != 0 ) glDeleteTextures( 1, &m_textureID );
}