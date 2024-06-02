
//#include "packetselector.h"

//PacketSelector::PacketSelector(const QVector<double>& signalData, QObject *parent) : QObject(parent), m_signalData(signalData)
//{
//    // Определяем пороговое значение
//    int sum = 0;
//    for (double value : signalData) {
//        sum += value;
//    }
//    threshold = sum / signalData.size();
//}

//PacketSelector::~PacketSelector()
//{
//}

//QVector<double> PacketSelector::selectPacket()
//{
//    int startIndex = 0;
//    int endIndex = 0;

//    for (int i = 0; i < m_signalData.size(); i++) {
//        if (m_signalData[i] > threshold) {
//            startIndex = i;
//            break;
//        }
//    }

//    for (int i = startIndex; i < m_signalData.size(); i++) {
//        if (m_signalData[i] < threshold) {
//            endIndex = i;
//            break;
//        }
//    }

//    m_selectedPacket.reserve(endIndex - startIndex);
//    for (int i = startIndex; i < endIndex; i++) {
//        m_selectedPacket.push_back(m_signalData[i]);
//    }

//    return m_selectedPacket;
//}
