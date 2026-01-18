//
// Created by 25137 on 25-12-21.
//

#ifndef NODEDATA_H
#define NODEDATA_H

#include <QtNodes/NodeData>
#include <QMetaEnum>
#include <QMap>
namespace QtNodes {
class NodeDataTypeEnum:public QObject {
  Q_OBJECT
public:

  // 修正枚举命名：避免使用IN/OUT这类可能与关键字冲突的名字
  enum InputType {          // 更好的命名
    IN_VIRTUAL_TX,
    IN_IO_TX,
    IN_IO_RX,
    IN_APP_TX,
    IN_APP_RX,
    IN_APP_SIGNAL
};
  Q_ENUM(InputType)        // 注册枚举到元对象系统

  enum OutputType {        // 更好的命名
    OUT_IO_TX,
    OUT_IO_RX,
    OUT_APP_TX,
    OUT_APP_RX,
    OUT_APP_SIGNAL,
};
  Q_ENUM(OutputType)      // 注册枚举到元对象系统

  // 修正模板函数
  template<typename T>
  static QString getEnumID(T value)  {
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    auto id = QString( metaEnum.valueToKey(static_cast<int>(value)));
      int index = id.indexOf("_");

      if (index != -1) {
          return id.mid(index+1);
      }
      else {
          return id;
      }
  }
  template<typename T>
  static QString getEnumName(T value)  {
    return getEnumID(value);
  };
};
  /// The class can potentially incapsulate any user data which
  /// need to be transferred within the Node Editor graph
/**
 * @brief 通用节点数据类模板
 * @tparam EnumType 枚举类型（InputType 或 OutputType）
 */
template<typename EnumType>
class TypedNodeData : public NodeData
{
public:
  explicit TypedNodeData(int id)
      : m_id(id)
      , m_type(
          NodeDataTypeEnum::getEnumID(static_cast<EnumType>(id)),
          NodeDataTypeEnum::getEnumName(static_cast<EnumType>(id))
        )
  {}

  explicit TypedNodeData(EnumType enumValue)
      : m_id(static_cast<int>(enumValue))
      , m_type(
          NodeDataTypeEnum::getEnumID(enumValue),
          NodeDataTypeEnum::getEnumName(enumValue)
        )
  {}

  NodeDataType type() const override { return m_type; }

  int id() const { return m_id; }
  EnumType enumValue() const { return static_cast<EnumType>(m_id); }

  // 可选的：添加特定类型的数据成员
  // 例如，如果你需要存储实际的数据值
  void setData(const QVariant& data) { m_data = data; }
  QVariant data() const { return m_data; }

  std::shared_ptr<NodeData> clone() const  {
    auto cloned = std::make_shared<TypedNodeData<EnumType>>(m_id);
    cloned->setData(m_data);
    return cloned;
  }

  QString toString() const  {
    return QString("%1 (ID: %2, Data: %3)")
        .arg(m_type.name)
        .arg(m_id)
        .arg(m_data.toString());
  }

private:
  int m_id;
  NodeDataType m_type;
  QVariant m_data;  // 可选的：存储实际数据
};

// 类型别名，方便使用
using INNodeData = TypedNodeData<NodeDataTypeEnum::InputType>;
using OUTNodeData = TypedNodeData<NodeDataTypeEnum::OutputType>;
};


#endif //NODEDATA_H
