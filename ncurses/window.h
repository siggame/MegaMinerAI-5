#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

class Window
{
  protected:
    WINDOW *mWindow;
    int mX, mY;
    int mWidth, mHeight;
    
    void createWindow();
    void deleteWindow();
  public:
    int getWidth()
    {
      return mWidth;
    }
    int getHeight()
    {
      return mHeight;
    }
    
  public:
    Window( int x, int y, int width, int height );
    ~Window();
    void moveWindow( int x, int y );
    void resizeWindow( int width, int height );
    virtual void update();
  
};

#endif
