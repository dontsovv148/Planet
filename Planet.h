#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>
static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T(" ");
HDC hdc;
 HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

extern const  int razx ; // ������ ������ ���� X
extern const  int razy;  // ������ ������ ���� Y

extern const int ex[] = { -1, 0, 0, 1, -1, -1,  1, 1 };      //��������� ��������� X
extern const int ey[] = { 0,-1, 1, 0, -1,  1, -1, 1 };       //��������� ��������� Y

extern const int ex1[] = { 0,0,0,0,    -1, -1,  0, 1 };      //��������� ��������� X(�������������� �������� 1 ��� �������� �� ���������)
extern const int ey1[] = { 0,0,0,0,     0,  0, -1, 0 };      //��������� ��������� Y(�������������� �������� 1 ��� �������� �� ���������)

extern const int ex2[] = { 0,0,0,0,     0,  0,  1, 0 };      //��������� ��������� X(�������������� �������� 2 ��� �������� �� ���������)
extern const int ey2[] = { 0,0,0,0,    -1,  1,  0, 1 };      //��������� ��������� Y(�������������� �������� 2 ��� �������� �� ���������)


 int marshrutx[1000000];    // ������ ��� ��������� �������� X
 int marshruty[1000000];    // ������ ��� ��������� �������� Y
 int      nach[1000000];     // ������ ������� ��������� ��������� ��� ����� �����

 int nmarshrut;        // ����� ��������� ������ � �������� ��� ��������� ��������
 int nlin;             //����� ����� �����
 int tn;              // ������� ����� ������ � �������� ��� ��������� ��������


 int finx;    // ���������� X ������ ��������
 int finy;    // ���������� Y ������ ��������
 int var;             // ����� �������� ����������� �������
 int sinx;    // ���������� X ������ ��������
 int siny;    // ���������� Y ������ ��������

int curx, cury;  // ���������� �������
int nobl;        // ����� ������ �� ����������
 CHAR  hah[200];  //������� ���������
 HBRUSH hBrush;
 HPEN hPen;
 HFONT hfont;

const int centx[] = { //������ ��������� ������� �������� ��������� X
    1076,
    1000,1038,1076,1114,1152,
    970,1001,1031,1061,1091, 1121,1151,1182,
    947,973,999,1025,1050, 1076,1102,1127, 1153,1179,1205,
    929,951,974,997,1019, 1042,1065,1087, 1110,1133,1155,1178,1201,1223,
    913,933,954,974,994, 1015,1035,1056, 1076,1096,1117,1137,1158, 1178,1198,1219,1239,
    899,919,939,958,978, 997,1017,1037, 1056,1076,1096,1115,1135, 1155,1174,1194,1213,1233, 1253,
    887,905,923,941,959, 977,995,1013, 1031,1049,1067,1085,1103, 1121,1139,1157,1175,1193, 1211,1229,1247, 1265,
    876,894,911,928,946, 963,980,998, 1015,1033,1050,1067,1085, 1102,1119,1137,1154,1172, 1189,1206,1224, 1241, 1258,1276,
    863,880,897,914,931, 948,965,982, 999, 1016, 1033,1050,1067,1085, 1102,1119,1136,1153,1170, 1187,1204,1221, 1238, 1255, 1272,1289,
    847,864,881,898,915, 932,949,966, 983, 1000, 1017,1034,1051,1068, 1084,1101,1118,1135,1152, 1169,1186,1203, 1220, 1237, 1254,1271,1288,1305,
    834,851,869,886,903, 920,938,955, 972, 990, 1007,1024,1041,1059, 1076,1093,1111,1128,1145, 1162,1180,1197, 1214, 1232, 1249,1266,1283,1301,1318,
    823,840,858,875,893, 910,928,945, 963, 980, 997,1015,1032,1050, 1067,1085,1102,1120,1137, 1155,1172,1189, 1207, 1224, 1242,1259,1277,1294,1312 ,1329,
    815,832,849,867,884, 902,919,937, 954, 971, 989,1006,1024,1041, 1059,1076,1093,1111,1128, 1146,1163,1181, 1198, 1215, 1233,1250,1268,1285,1303 ,1320,1337,
    809,827,845,862,880, 898,916,934, 951, 969, 987,1005,1023,1040, 1058,1076,1094,1112,1129, 1147,1165,1183, 1201, 1218, 1236,1254,1272,1290,1307 ,1325,1343,
    806,824,842,860,878, 896,914,932, 950, 968, 986,1004,1022,1040, 1058,1076,1094,1112,1130, 1148,1166,1184, 1202, 1220, 1238,1256,1274,1292,1310 ,1328,1346,
    806,824,842,860,878, 896,914,932, 950, 968, 986,1004,1022,1040, 1058,1076,1094,1112,1130, 1148,1166,1184, 1202, 1220, 1238,1256,1274,1292,1310 ,1328,1346,
    809,827,845,862,880, 898,916,934, 951, 969, 987,1005,1023,1040, 1058,1076,1094,1112,1129, 1147,1165,1183, 1201, 1218, 1236,1254,1272,1290,1307 ,1325,1343,
    815,832,849,867,884, 902,919,937, 954, 971, 989,1006,1024,1041, 1059,1076,1093,1111,1128, 1146,1163,1181, 1198, 1215, 1233,1250,1268,1285,1303 ,1320,1337,
    823,840,858,875,893, 910,928,945, 963, 980, 997,1015,1032,1050, 1067,1085,1102,1120,1137, 1155,1172,1189, 1207, 1224, 1242,1259,1277,1294,1312 ,1329,
    834,851,869,886,903, 920,938,955, 972, 990, 1007,1024,1041,1059, 1076,1093,1111,1128,1145, 1162,1180,1197, 1214, 1232, 1249,1266,1283,1301,1318,
    847,864,881,898,915, 932,949,966, 983, 1000, 1017,1034,1051,1068, 1084,1101,1118,1135,1152, 1169,1186,1203, 1220, 1237, 1254,1271,1288,1305,
    863,880,897,914,931, 948,965,982, 999, 1016, 1033,1050,1067,1085, 1102,1119,1136,1153,1170, 1187,1204,1221, 1238, 1255, 1272,1289,
    876,894,911,928,946, 963,980,998, 1015,1033,1050,1067,1085, 1102,1119,1137,1154,1172, 1189,1206,1224, 1241, 1258,1276,
    887,905,923,941,959, 977,995,1013, 1031,1049,1067,1085,1103, 1121,1139,1157,1175,1193, 1211,1229,1247, 1265,
    899,919,939,958,978, 997,1017,1037, 1056,1076,1096,1115,1135, 1155,1174,1194,1213,1233, 1253,
    913,933,954,974,994, 1015,1035,1056, 1076,1096,1117,1137,1158, 1178,1198,1219,1239,
    929,951,974,997,1019, 1042,1065,1087, 1110,1133,1155,1178,1201,1223,
    947,973,999,1025,1050, 1076,1102,1127, 1153,1179,1205,
    970,1001,1031,1061,1091, 1121,1151,1182,
    1000,1038,1076,1114,1152,
    1076,
    1561,1599,1637,1675,1713,
    1531,1562,1592,1622,1652, 1682,1712,1743,
    1508,1534,1560,1586,1611, 1637,1663,1688, 1714,1740,1766,
    1490,1512,1535,1558,1580, 1603,1626,1648, 1671,1694,1716,1739,1762,1784,
    1474,1494,1515,1535,1555, 1576,1596,1617, 1637,1657,1678,1698,1719, 1739,1759,1780,1800,
    1460,1480,1500,1519,1539, 1558,1578,1598, 1617,1637,1657,1676,1696, 1716,1735,1755,1774,1794, 1814,
    1448,1466,1484,1502,1520, 1538,1556,1574, 1592,1610,1628,1646,1664, 1682,1700,1718,1736,1754, 1772,1790,1808, 1826,
    1437,1455,1472,1489,1507, 1524,1541,1559, 1576, 1594, 1611,1628,1646,1663, 1680,1698,1715,1733,1750, 1767,1785,1802, 1819, 1837,
    1424,1441,1458,1475,1492, 1509,1526,1543, 1560, 1577, 1594,1611,1628,1646, 1663,1680,1697,1714,1731, 1748,1765,1782, 1799, 1816, 1833,1850,
    1408,1425,1442,1459,1476, 1493,1510,1527, 1544, 1561, 1578,1595,1612,1629, 1645,1662,1679,1696,1713, 1730,1747,1764, 1781, 1798, 1815,1832,1849,1866,
    1395,1412,1430,1447,1464, 1481,1499,1516, 1533, 1551, 1568,1585,1602,1620, 1637,1654,1672,1689,1706, 1723,1741,1758, 1775, 1793, 1810,1827,1844,1862,1879,
    1384,1401,1419,1436,1454, 1471,1489,1506, 1524, 1541, 1558,1576,1593,1611, 1628,1646,1663,1681,1698, 1716,1733,1750, 1768, 1785, 1803,1820,1838,1855,1873 ,1890,
    1376,1393,1410,1428,1445, 1463,1480,1498, 1515, 1532, 1550,1567,1585,1602, 1620,1637,1654,1672,1689, 1707,1724,1742, 1759, 1776, 1794,1811,1829,1846,1864 ,1881,1898,
    1370,1388,1406,1423,1441, 1459,1477,1495, 1512, 1530, 1548,1566,1584,1601, 1619,1637,1655,1673,1690, 1708,1726,1744, 1762, 1779, 1797,1815,1833,1851,1868 ,1886,1904,
    1367,1385,1403,1421,1439, 1457,1475,1493, 1511, 1529, 1547,1565,1583,1601, 1619,1637,1655,1673,1691, 1709,1727,1745, 1763, 1781, 1799,1817,1835,1853,1871 ,1889,1907,
    1367,1385,1403,1421,1439, 1457,1475,1493, 1511, 1529, 1547,1565,1583,1601, 1619,1637,1655,1673,1691, 1709,1727,1745, 1763, 1781, 1799,1817,1835,1853,1871 ,1889,1907,
    1370,1388,1406,1423,1441, 1459,1477,1495, 1512, 1530, 1548,1566,1584,1601, 1619,1637,1655,1673,1690, 1708,1726,1744, 1762, 1779, 1797,1815,1833,1851,1868 ,1886,1904,
    1376,1393,1410,1428,1445, 1463,1480,1498, 1515, 1532, 1550,1567,1585,1602, 1620,1637,1654,1672,1689, 1707,1724,1742, 1759, 1776, 1794,1811,1829,1846,1864 ,1881,1898,
    1384,1401,1419,1436,1454, 1471,1489,1506, 1524, 1541, 1558,1576,1593,1611, 1628,1646,1663,1681,1698, 1716,1733,1750, 1768, 1785, 1803,1820,1838,1855,1873 ,1890,
    1395,1412,1430,1447,1464, 1481,1499,1516, 1533, 1551, 1568,1585,1602,1620, 1637,1654,1672,1689,1706, 1723,1741,1758, 1775, 1793, 1810,1827,1844,1862,1879,
    1408,1425,1442,1459,1476, 1493,1510,1527, 1544, 1561, 1578,1595,1612,1629, 1645,1662,1679,1696,1713, 1730,1747,1764, 1781, 1798, 1815,1832,1849,1866,
    1424,1441,1458,1475,1492, 1509,1526,1543, 1560, 1577, 1594,1611,1628,1646, 1663,1680,1697,1714,1731, 1748,1765,1782, 1799, 1816, 1833,1850,
    1437,1455,1472,1489,1507, 1524,1541,1559, 1576, 1594, 1611,1628,1646,1663, 1680,1698,1715,1733,1750, 1767,1785,1802, 1819, 1837,
    1448,1466,1484,1502,1520, 1538,1556,1574, 1592,1610,1628,1646,1664, 1682,1700,1718,1736,1754, 1772,1790,1808, 1826,
    1460,1480,1500,1519,1539, 1558,1578,1598, 1617,1637,1657,1676,1696, 1716,1735,1755,1774,1794, 1814,
    1474,1494,1515,1535,1555, 1576,1596,1617, 1637,1657,1678,1698,1719, 1739,1759,1780,1800,
    1490,1512,1535,1558,1580, 1603,1626,1648, 1671,1694,1716,1739,1762,1784,
    1508,1534,1560,1586,1611, 1637,1663,1688, 1714,1740,1766,
    1531,1562,1592,1622,1652, 1682,1712,1743,
    1561,1599,1637,1675,1713
};
const int centy[] = {  //������ ��������� ������� �������� ��������� Y
    6,
    17,17,17,17,17,
    28,28,28,28,28,28,28,28,
    39,39,39,39,39,39,39,39,39,39,39,
    50,50,50,50,50,50,50,50,50,50,50,50,50,50,
    61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,
    72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,
    83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
    94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,
    110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,
    133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,
    157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,
    183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,
    210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,
    238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,
    266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,
    294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,
    322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,
    350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,
    377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,
    403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,
    427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,
    450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,
    466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,
    477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,
    488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,
    499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,
    510,510,510,510,510,510,510,510,510,510,510,510,510,510,
    521,521,521,521,521,521,521,521,521,521,521,
    532,532,532,532,532,532,532,532,
    543,543,543,543,543,
    554,
    17,17,17,17,17,
    28,28,28,28,28,28,28,28,
    39,39,39,39,39,39,39,39,39,39,39,
    50,50,50,50,50,50,50,50,50,50,50,50,50,50,
    61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,
    72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,
    83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,83,
    94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,
    110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,
    133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,133,
    157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,157,
    183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,183,
    210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,
    238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,238,
    266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,266,
    294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294,
    322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,322,
    350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,350,
    377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,377,
    403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,403,
    427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,427,
    450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,450,
    466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,466,
    477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,477,
    488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,488,
    499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,499,
    510,510,510,510,510,510,510,510,510,510,510,510,510,510,
    521,521,521,521,521,521,521,521,521,521,521,
    532,532,532,532,532,532,532,532,
    543,543,543,543,543,
};
BOOL Shar(HDC hdc); // ��������� ���������
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2);  // ��������� �����
INT Risob(int x, int y, int k, int b);   // ��������� ������� �� ����� ����
INT Planet();    // �������� ���� � ����
INT Rissusha();  // ��������� ���� - ������� �����
INT Vibvar();    //  ����� �������� ����������� �������