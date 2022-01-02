/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ContactLabel
*/

#include "ContactLabel.h"

ContactLabel::ContactLabel(UserApp user, QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f), _user(user)
{
}

ContactLabel::~ContactLabel()
{
}

UserApp ContactLabel::getUser()
{
    return _user;
}

void ContactLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(_user);
}
