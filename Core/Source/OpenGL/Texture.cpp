#include "OpenGL/Texture.h"

#include "stb_image.h"
#include "ModernLogger.h"

#include <GL/glew.h>

Texture::Texture()
    : m_textureID( 0 ), m_width( 0 ), m_height( 0 ),  m_internalFormat( GL_RED ),
    m_imageFormat( GL_RED ), m_wrapS( GL_CLAMP_TO_EDGE ), m_wrapT( GL_CLAMP_TO_EDGE ), m_filterMin( GL_LINEAR ),
    m_filterMax( GL_LINEAR ), m_imageWidth( 0 ), m_imageHeight( 0 ), m_imageBitDepth( 0 ) {

}

Texture::~Texture() {
    // Never clear OpenGL resources in deconstructor
}

// For Text Rendering...
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

// For loading textures for meshes...
void Texture::LoadTexture( const char *fileLocation ) {
    stbi_set_flip_vertically_on_load( true );

    unsigned char *textureData = stbi_load( fileLocation, &m_imageWidth, &m_imageHeight, &m_imageBitDepth, 0 );
    if( textureData == 0 ) {
        TheMLogger::Instance()->Error( "Texture {} failed to load.", fileLocation );
        return;
    }

    TheMLogger::Instance()->Info( "Loaded texture {}. It's {} by {} at {} bit depth.", fileLocation, m_imageWidth, m_imageHeight, m_imageBitDepth );

    glGenTextures( 1, &m_textureID );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, m_textureID );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if( m_imageBitDepth == 4 ) {
        // PNG with alpha channel
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData );
    }
    else if( m_imageBitDepth == 3 ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData );
    }
    else if( m_imageBitDepth == 1 ) {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, textureData );
    } else {
        TheMLogger::Instance()->Error( "Texture {} failed to load on the GPU. Not a valid bit depth.", fileLocation );
    }
    glGenerateMipmap( GL_TEXTURE_2D );

    // Clean up
    glBindTexture( GL_TEXTURE_2D, 0 );
    stbi_image_free( textureData );
}

void Texture::Bind( unsigned int slot ) const {
    glActiveTexture( GL_TEXTURE0 + slot );
    glBindTexture( GL_TEXTURE_2D, this->m_textureID );
}

void Texture::Unbind( unsigned int slot ) const {
    glActiveTexture( GL_TEXTURE0 + slot );
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::Clean() {
    if( m_textureID != 0 ) glDeleteTextures( 1, &m_textureID );
}