#include "QCalculatorUI.h"

QCalculatorUI::QCalculatorUI() : QWidget(nullptr, Qt::WindowCloseButtonHint)
{
    m_cal = nullptr;
}

bool QCalculatorUI::construct()
{
    bool ret = true;
    const char* btnText[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C",
    };

    m_edit = new QLineEdit(this);

    if( m_edit != nullptr )
    {
        m_edit->move(10, 10);
        m_edit->resize(240, 30);
        m_edit->setReadOnly(true);
        m_edit->setAlignment(Qt::AlignRight);
    }
    else
    {
        ret = false;
    }

    for(int i=0; (i<4) && ret; i++)
    {
        for(int j=0; (j<5) && ret; j++)
        {
            m_button[i*5 + j] = new QPushButton(this);

            if( m_button[i*5 + j] != nullptr )
            {
                m_button[i*5 + j]->resize(40, 40);
                m_button[i*5 + j]->move(10 + (10 + 40)*j, 50 + (10 + 40)*i);
                m_button[i*5 + j]->setText(btnText[i*5 + j]);

                connect(m_button[i*5 + j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));
            }
            else
            {
                ret = false;
            }
        }
    }

    return ret;
}

QCalculatorUI* QCalculatorUI::NewInstance()
{
    QCalculatorUI* ret = new QCalculatorUI();

    if( (ret == nullptr) || !ret->construct() )
    {
        delete ret;
        ret = nullptr;
    }

    return ret;
}

void QCalculatorUI::show()
{
    QWidget::show();

    setFixedSize(width(), height());
}

void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    if( btn != NULL )
    {
        QString clickText = btn->text();

        if( clickText == "<-" )
        {
            QString text = m_edit->text();

            if( text.length() > 0 )
            {
                text.remove(text.length()-1, 1);

                m_edit->setText(text);
            }
        }
        else if( clickText == "C" )
        {
            m_edit->setText("");
        }
        else if( clickText == "=" )
        {
            if( m_cal != nullptr )
            {
                m_cal->expression(m_edit->text());
                m_edit->setText(m_cal->result());
            }
        }
        else
        {
            m_edit->setText(m_edit->text() + clickText);
        }
    }
}

void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

ICalculator* QCalculatorUI::getCalculator()
{
    return m_cal;
}

QCalculatorUI::~QCalculatorUI()
{

}
