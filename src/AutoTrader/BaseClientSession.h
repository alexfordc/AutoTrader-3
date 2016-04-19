#ifndef BASE_CLIENT_SESSION_H
#define BASE_CLIENT_SESSION_H


#include <string>
#include <memory>
#include <mutex>
#include <future>
#include <chrono>
#include <thread>
#include <atomic>
#include <condition_variable>

class Order;
class TickWrapper;
class CtpTradeSpi;
class RealTimeDataProcessor;
class CThostFtdcTraderApi;

namespace AP{
	class AccountDetailMgr;
}

namespace Account{
	struct Meta;
}

typedef int ErrorCode;

class BaseClientSession
{
public:
	BaseClientSession(const std::string& userId);
	virtual ~BaseClientSession();
	virtual bool Init_CTP();
	virtual void SendTickToClient(const TickWrapper& tick) = 0;	

	//These below two Functions should be syncd with one mutex, they may conflict with m_pending_order
	bool AppendOrder(const Order& order);//multi-thread notice
	void WaitAndPopCurrentOrder(Order& ord);//multi-thread notice

	bool IsTrading() const { return m_isTrading.load(); }
	bool IsPositionInfoReady() const { return m_PositionInfo_ready.load(); }
	std::string UserId() const { return m_userId; };

	bool StartTrade(const std::string& instru, const std::string& strategyName, ErrorCode& errcode);
	void StopTrade();

protected:
	bool ExecutePendingOrder();

protected:
	std::string										m_userId;
	std::atomic<bool>                               m_isTrading; // access by thread-OrderExecutor and thread-ActionQueueInvoker
	std::unique_ptr<AP::AccountDetailMgr>           m_detailMgr;
	std::atomic<bool>                               m_PositionInfo_ready;//access by thread-tradespi and thread-ActionQueueInvoker
	int                                             m_total_vol;
	bool                                            m_ReleaseingCtpAccount;

	std::unique_ptr<Order>                          m_pending_order;
	CtpTradeSpi*									m_trade_spi;
	CThostFtdcTraderApi*                            m_trade_api;
	
	std::mutex                                      m_mtx;
	std::condition_variable                         m_con;
	std::future<bool>                               m_orderExecuteThreadF;
	
};

#endif