#include "window.h"

Window::Window( int x, int y, int width, int height )
{
  mX = x;
  mY = y;
  mWidth = width;
  mHeight = height;
  createWindow();
  wrefresh( mWindow );

}

Window::~Window()
{
  deleteWindow();

}

void Window::createWindow()
{
  refresh();
  mWindow = newwin( mHeight, mWidth, mY, mX);
  box( mWindow, 0, 0 );
  wrefresh( mWindow );
}

void Window::deleteWindow()
{
  werase( mWindow );
  wattrset( mWindow, 0 );
  wrefresh( mWindow );
  delwin( mWindow );
}

void Window::moveWindow( int x, int y )
{
  deleteWindow();
  mX = x;
  mY = y;
  createWindow();
}

void Window::resizeWindow( int width, int height )
{
  deleteWindow();
  mWidth = width;
  mHeight = height;
  createWindow();
}

void Window::update()
{
  wrefresh( mWindow );
}
