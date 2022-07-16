#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonObject>
#include<QDebug>
#include<QFile>

void MainWindow::writeJson()
{
    QJsonObject obj;
    obj.insert("name","Ace");
    obj.insert("sex","man");
    obj.insert("age",20);

    QJsonObject subObj;
    subObj.insert("father","Gol·D·Roge");
    subObj.insert("mother","Portagas·D·Rouge");
    QJsonArray array;
    array.append("Sabo");
    array.append("Monkey D. Luffy");
    subObj.insert("brother",array);

    obj.insert("family",subObj);
    obj.insert("InAlive",false);
    obj.insert("Comment:","yyds");

    //进行json转换和写入文件
    QJsonDocument doc(obj);
    QByteArray json=doc.toJson();

    QFile file("ace.json");
    file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}

void MainWindow::readJson()
{
    QFile file("ace.json");
    file.open(QFile::ReadOnly);
    QByteArray all=file.readAll();
    file.close();

    QJsonDocument doc=QJsonDocument::fromJson(all);
    if(doc.isObject()){
        QJsonObject obj=doc.object();
        QStringList keys=obj.keys();
        for(auto i:keys){
            QJsonValue value=obj.value(i);
            if(value.isBool()){
                qDebug()<<i<<":"<<value.toBool();
            }
            else if(value.isString()){
                qDebug()<<i<<":"<<value.toString();
            }
            else if(value.isDouble()){
                qDebug()<<i<<":"<<value.toInt();
            }
            else if(value.isObject()){
                qDebug()<<i<<":";
                QJsonObject subObj=value.toObject();
                QStringList subKeys=subObj.keys();
                for(auto j:subKeys){
                    QJsonValue subValue=subObj.value(j);
                    if(subValue.isString()){
                        qDebug()<<" "<<j<<":"<<subValue.toString();
                    }
                    else if(subValue.isArray()){
                        QJsonArray array=subValue.toArray();
                        for(auto k:array){
                            qDebug()<<"! "<<k.toString();
                        }
                    }
                }
            }
        }
    }
}
//我们演示了将数据转换为json和解析json。解析json实际没这么复杂，我们只是演示了API
//QJsonDocument我们只使用了一次，是将QJsonObject对象转换为QString然后写入文件。
//Qt会自动将json按照升序排序