#include "DbManager.h"
#include <MySqlConnector.h>
DbManager::DbManager( const std::string& host, const std::string& database, const std::string& user, const std::string& pw, uint16_t port ) :
  m_host( host ),
  m_database( database ),
  m_user( user ),
  m_password( pw ),
  m_port( port )	
{
}

DbManager::~DbManager()
{

}

bool DbManager::connect()
{
  std::shared_ptr< Mysql::MySqlBase > base( new Mysql::MySqlBase() );
  Mysql::optionMap options;
  options[ Mysql::MYSQL_OPT_RECONNECT ] = "1";
  options[ Mysql::MYSQL_SET_CHARSET_NAME ] = "utf8";

  try
  {
    m_pConnection = base->connect( m_host, m_user, m_password, options, m_port );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

bool DbManager::selectSchema()
{
  if( !m_pConnection )
  {
    m_lastError = "No valid db connection!";	  
    return false;
  }

  try
  {
    m_pConnection->setSchema( m_database );
  }
  catch( std::runtime_error& e )
  {
    m_lastError = e.what();
    return false;
  }
  return true;
}

const std::string& DbManager::getLastError()
{
  return m_lastError;
}

void DbManager::setMode( Mode mode )
{
  m_mode = mode;
}

Mode DbManager::getMode() const
{
  return m_mode;
}