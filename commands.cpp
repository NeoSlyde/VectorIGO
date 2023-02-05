#include "commands.h"

static constexpr int setShapeRectCommandId = 1;
static constexpr int setShapeColorCommandId = 2;


AddCommand::AddCommand(VScene *scene, VShape *shape, QUndoCommand *parent)
    : QUndoCommand(parent), _scene(scene), _shape(shape)
{
}

void AddCommand::undo()
{
    _scene->removeItem(_shapeName);
}

void AddCommand::redo()
{
    // A shape only gets a name when it is inserted into a document
    _scene->addItem(_shape);
    setText(QObject::tr("Add %1").arg("ui"));
}

RemoveCommand::RemoveCommand(VScene *scene, const QString &shapeName,
                                       QUndoCommand *parent)
    : QUndoCommand(parent), _scene(scene), _shape(scene->shape(shapeName)) // TODO: Create shape() that returns the shape
    , _shapeName(shapeName)
{
    setText(QObject::tr("Remove %1").arg(shapeName));
}

void RemoveCommand::undo()
{
    _scene->addItem(_shape);
}

void RemoveCommand::redo()
{
    _scene->removeItem(_shapeName);
}

/******************************************************************************
** SetShapeColorCommand


SetShapeColorCommand::SetShapeColorCommand(VScene *scene, const QString &shapeName,
                                           const QColor &color, QUndoCommand *parent)
    : QUndoCommand(parent), _scene(scene), _shapeName(shapeName)
    , _oldColor(scene->shape(shapeName).color()), _newColor(color)
{
    setText(QObject::tr("Set %1's color").arg(shapeName));
}

void SetShapeColorCommand::undo()
{
    _scene->setShapeColor(_shapeName, _oldColor);
}

void SetShapeColorCommand::redo()
{
    m_doc->setShapeColor(m_shapeName, m_newColor);
}

bool SetShapeColorCommand::mergeWith(const QUndoCommand *command)
{
    if (command->id() != setShapeColorCommandId)
        return false;

    const SetShapeColorCommand *other = static_cast<const SetShapeColorCommand*>(command);
    if (m_shapeName != other->m_shapeName)
        return false;

    m_newColor = other->m_newColor;
    return true;
}

int SetShapeColorCommand::id() const
{
    return setShapeColorCommandId;
}

/******************************************************************************
** SetShapeRectCommand

SetShapeRectCommand::SetShapeRectCommand(Document *doc, const QString &shapeName,
                                         const QRect &rect, QUndoCommand *parent)
    : QUndoCommand(parent), m_doc(doc), m_shapeName(shapeName)
    , m_oldRect(doc->shape(shapeName).rect()), m_newRect(rect)
{
    setText(QObject::tr("Change %1's geometry").arg(shapeName));
}

void SetShapeRectCommand::undo()
{
    m_doc->setShapeRect(m_shapeName, m_oldRect);
}

void SetShapeRectCommand::redo()
{
    m_doc->setShapeRect(m_shapeName, m_newRect);
}

bool SetShapeRectCommand::mergeWith(const QUndoCommand *command)
{
    if (command->id() != setShapeRectCommandId)
        return false;

    const SetShapeRectCommand *other = static_cast<const SetShapeRectCommand*>(command);
    if (m_shapeName != other->m_shapeName)
        return false;

    m_newRect = other->m_newRect;
    return true;
}


int SetShapeRectCommand::id() const
{
    return setShapeRectCommandId;
}
*/
