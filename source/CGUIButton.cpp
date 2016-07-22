#include <CGUIButton.h>

CGUIButton::CGUIButton(IrrlichtDevice *device)
{
    Device = device;
    Video = Device->getVideoDriver();
    Gui = Device->getGUIEnvironment();
    Scale = vector2df(100,100);

    //Add our button
    Button = Gui->addButton(rect<s32>(0,0, 100, 100), 0, 0,
                            L"New Button", L"Tooltip");

}

CGUIButton::~CGUIButton(void)
{
    if (Button)
        Button->remove();
}

void CGUIButton::setToolTipText(const wchar_t* text)
{
    Button->setToolTipText(text);
}

void CGUIButton::setRelativePosition(vector2df position)
{
    const core::rect<s32>& rectangle = rect<s32>(position.X, position.Y, position.X + Scale.X, position.Y + Scale.Y);
    Button->setRelativePosition(rectangle);
}

vector2df CGUIButton::getRelativePosition()
{
    const core::rect<s32>& rectangle = Button->getRelativePosition();
    return vector2df(rectangle.UpperLeftCorner.X, rectangle.UpperLeftCorner.Y);
}

void CGUIButton::setRelativeScale(vector2df scale)
{
    const core::rect<s32>& rectangle = Button->getRelativePosition();
    scale = vector2df(scale.X * 100, scale.Y * 100);
    Button->setRelativePosition(core::rect<s32>(rectangle.UpperLeftCorner.X, rectangle.UpperLeftCorner.Y, rectangle.UpperLeftCorner.X + scale.X, rectangle.UpperLeftCorner.Y + scale.Y));
}

void CGUIButton::setScale(vector2df scale)
{

}

void CGUIButton::setPosition(vector2df position)
{
    Button->setRelativePosition(core::rect<s32>(position.X - Scale.X, position.Y - Scale.Y, position.X + Scale.X, position.Y + Scale.Y));
}
