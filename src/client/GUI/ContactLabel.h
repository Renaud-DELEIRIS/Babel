/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** ContactLabel
*/


#include <QLabel>
#include <QWidget>
#include <Qt>
#include "common/User.hpp"

#ifndef CONTACTLABEL_HPP_
#define CONTACTLABEL_HPP_

class ContactLabel : public QLabel {
    Q_OBJECT

    public:
        explicit ContactLabel(UserApp user, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
        virtual ~ContactLabel();
        UserApp getUser();

    signals:
        void clicked(UserApp);

    protected:
        void mousePressEvent(QMouseEvent* event);

    private:
        UserApp _user;
};

#endif /* !CONTACTLABEL_HPP_ */
