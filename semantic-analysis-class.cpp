#include "semantic-analysis-class.hpp"

analysis::Semantic::Semantic()
    : m_tree_ptr(nullptr), m_symbol_head(std::make_shared<ast::SymbolTable>()), m_messages(), m_error_count(0), m_warning_count(0)
{
}
analysis::Semantic::Semantic(ast::Tree *tree)
    : m_tree(tree), m_symbol_head(std::make_shared<ast::SymbolTable>()), m_messages(), m_err_count(0), m_warn_count(0)
{
}
void analysis::Semantic::Initialize(ast::Tree *tree)
{
  m_tree = tree;
}
int analysis::Semantic::Analyze()
{
}
void analysis::Semantic::push_back(Message const &msg)
{
  m_messages.push_back(msg);
  m_error_count += (msg.type == Message::Type::kError);
  m_warning_count += (msg.type == Message::Type::kWarning);
}

analysis::Message &analysis::Semantic::emplace_back(Message::loc_type const &loc, Message::Type const type, std::string const &what)
{
  m_message.emplace_back(loc, type, what);
  m_error_count += (type == Message::Type::kError);
  m_warning_count += (type == Message::Type::kWarning);
  return m_message.back();
}
void analysis::Semantic::CreateSymbolTable()
{
  if (m_tree == nullptr)
    throw;
  auto head = m_tree->GetHead();
  AnalyzeNode(&head);
}