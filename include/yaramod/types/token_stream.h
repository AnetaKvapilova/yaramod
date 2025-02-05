/**
 * @file src/types/token_stream.h
 * @brief Declaration of class TokenStream.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#pragma once

#include <list>
#include <vector>

#include "yaramod/types/token.h"

namespace yaramod {

/**
 * A container storing all parsed tokens. Formated text of the parsed input is accessible with getText method or <<operator.
 */
class TokenStream
{
public:
	/**
	 * Class serves as a context storage for printing TokenStream and determining comment alignment.
	 */
	class PrintHelper
	{
	public:
		std::size_t getCurrentLine() const { return lineCounter; }
		const std::vector<TokenIt>& getCommentPool() const { return commentPool; }

		std::size_t insertIntoStream(std::stringstream* ss, char what);
		std::size_t insertIntoStream(std::stringstream* ss, const std::string& what, std::size_t length = 0);
		std::size_t insertIntoStream(std::stringstream* ss, TokenStream* ts, TokenIt what);
		std::size_t printComment(std::stringstream* ss, TokenStream* ts, TokenIt it, bool alignComment);
	private:
		std::size_t lineCounter = 0;
		std::size_t columnCounter = 0;
		bool commentOnThisLine = false;
		std::size_t maximalCommentColumn = 0;
		std::vector<TokenIt> commentPool;
	};

	TokenStream() = default;

	/// @name Insertion methods
	/// @{
	TokenIt emplace_back(TokenType type, char value);
	template <typename Value, typename T>
	TokenIt emplace_back(TokenType type, Value&& value, T&& formatted_value)
	{
		_tokens.emplace_back(type, Literal(std::forward<Value>(value), std::forward<T>(formatted_value)));
		return --_tokens.end();
	}
	template <typename Value>
	TokenIt emplace_back(TokenType type, Value&& value)
	{
		_tokens.emplace_back(type, Literal(std::forward<Value>(value)));
		return --_tokens.end();
	}
	TokenIt emplace_back(TokenType type, const Literal& literal);
	TokenIt emplace_back(TokenType type, Literal&& literal);

	TokenIt emplace(const TokenIt& before, TokenType type, char value);
	template <typename Value, typename T>
	TokenIt emplace(const TokenIt& before, TokenType type, Value&& value, T&& formatted_value)
	{
		_tokens.emplace(before, type, Literal(std::forward<Value>(value), std::forward<T>(formatted_value)));
		auto output = before;
		return --output;
	}
	template <typename Value>
	TokenIt emplace(const TokenIt& before, TokenType type, Value&& value)
	{
		_tokens.emplace(before, type, Literal(std::forward<Value>(value)));
		auto output = before;
		return --output;
	}
	TokenIt emplace(const TokenIt& before, TokenType type, const Literal& literal);
	TokenIt emplace(const TokenIt& before, TokenType type, Literal&& literal);

	TokenIt push_back(const Token& t);
	TokenIt push_back(Token&& t);
	TokenIt insert(TokenIt before, TokenType type, const Literal& literal);
	TokenIt insert(TokenIt before, TokenType type, Literal&& literal);
	TokenIt erase(TokenIt element);
	TokenIt erase(TokenIt first, TokenIt last);
	void move_append(TokenStream* donor);
	void move_append(TokenStream* donor, TokenIt before);
	/// @}

	/// @name Iterators
	/// @{
	TokenIt begin();
	TokenIt end();
	TokenConstIt begin() const;
	TokenConstIt end() const;
	TokenItReversed rbegin();
	TokenItReversed rend();
	TokenConstItReversed rbegin() const;
	TokenConstItReversed rend() const;
	/// @}

	/// @name Capacity
	/// @{
	std::size_t size() const;
	bool empty() const;
	/// @}

	/// @name Lookaround methods
	/// @{
	TokenIt find(TokenType type);
	TokenIt find(TokenType type, TokenIt from);
	TokenIt find(TokenType type, TokenIt from, TokenIt to);
	TokenIt findBackwards(TokenType type);
	TokenIt findBackwards(TokenType type, TokenIt to);
	TokenIt findBackwards(TokenType type, TokenIt from, TokenIt to);
	/// @}

	/// @name Text representation
	/// @{
	friend std::ostream& operator<<(std::ostream& os, TokenStream& ts) { return os << ts.getText(false); }
	std::string getText(bool withIncludes = false, bool alignComments = true);
	std::vector<std::string> getTokensAsText() const;
	/// @}

	/// @name Reseting method
	void clear();
	/// @}
protected:
	void getTextProcedure(PrintHelper& helper, std::stringstream* os, bool withIncludes, bool alignComments);
	void autoformat();
	void determineNewlineSectors();
	void addMissingNewLines();

	std::optional<TokenIt> predecessor(TokenIt it);
private:
	std::list<Token> _tokens; ///< All tokens off the rule
	bool formatted = false; ///< The flag is set once autoformat has been called
};

} //namespace yaramod
