==================
Master programming
==================

-----------------------------------
Лекция №9 (boost::spirit)
-----------------------------------

:Author: Игорь Шаронов
:Date: 2018-10-14

Знакомство с boost::spirit
==========================

Из чего состоит грамматика языка?
---------------------------------

.. table:: PEG Operators
    :type: csv
    :delimiter: ;

::
    Description;PEG;Spirit X3;Example
    Sequence;a b;a >> b;``int_ >> ' ' >> double_``
    Alternative;a|b;a|b;``alpha | digit``
    Zero or more (Kleene);a*;*a;``alpha >> *(',' >> alnum)``
    One or more (Plus);a+;+a;``+alnum >> '_'``
    Optional;a?;-a;``-alpha >> int_``
    And-predicate;&a;&a;``int_ >> &char_(';')``
    Not-predicate;!a;!a;``~char_('"')``
    Difference;;a - b;``"/*" >> *(char_ - "*/") >> "*/"``
    Expectation;;a > b;``lit('c') > "++"``
    List;;a % b;``int_ % ','``

``boost::spirit::x3 <https://ciere.com/cppnow15/using_x3.pdf>``

x3::rule<ID, Attribute>

* Synthesized attribute --- атрибут по умолчанию
* Compatible attribute --- совместимый (конвертируемый) атрибут (``std::string`` и ``std::vector<char>``)


