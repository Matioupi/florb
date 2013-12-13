#ifndef GFX_HPP
#define GFX_HPP

#include <FL/x.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>

typedef Fl_Offscreen canvas_storage;
typedef Fl_Image* image_storage;

class image;
class color;

// Represents any kind of surface that can be drawn on
class drawable
{
    public:
        virtual unsigned int w() = 0;
        virtual unsigned int h() = 0;
        virtual void fillrect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b) = 0;
    private: 
};

// An in-memory drawing buffer 
class canvas : public drawable
{
    public:
        canvas(unsigned int w, unsigned int h);
        ~canvas();

        void resize(unsigned int w, unsigned int h);
        void draw(canvas& src, int srcx, int srcy, int srcw, int srch, int dstx, int dsty);
        void draw(image &src, int dstx, int dsty);
        void fillrect(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b);
        canvas_storage buf(void) { trycreate(); return m_buf; };
        void buf(canvas_storage bufs) { m_buf = bufs; };
        unsigned int w(void) { return m_w; };
        unsigned int h(void) { return m_h; };
        void w(unsigned int ws) { m_w = ws; };
        void h(unsigned int hs) { m_h = hs; };

    private:
        bool m_init;
        unsigned int m_w;
        unsigned int m_h;
        canvas_storage m_buf;

        void trycreate(void);
};

class image
{
    public:
        image(int type, const unsigned char *buffer, int bufsize);
        ~image();

        image_storage buf(void) { return m_buf; };
        int type() { return m_type; };
        void buf(image_storage bufs) { m_buf = bufs; };

        enum {
            PNG,
            JPG
        };

    private:
        int m_type;
        bool m_init;
        image_storage m_buf;
};

#endif // GFX_HPP
