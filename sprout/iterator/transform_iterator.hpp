#ifndef SPROUT_ITERATOR_TRANSFORM_ITERATOR_HPP
#define SPROUT_ITERATOR_TRANSFORM_ITERATOR_HPP

#include <iterator>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/iterator/prev.hpp>
#include <sprout/iterator/distance.hpp>

namespace sprout {
	//
	// transform_iterator
	//
	template<typename BinaryFunction, typename LIterator, typename RIterator = void>
	class transform_iterator
		: public std::iterator<
			typename std::iterator_traits<LIterator>::iterator_category,
			typename std::remove_reference<
				typename std::result_of<
					BinaryFunction (
						typename std::iterator_traits<LIterator>::reference,
						typename std::iterator_traits<RIterator>::reference
						)
				>::type
			>::type,
			typename std::iterator_traits<LIterator>::difference_type,
			typename std::remove_reference<
				typename std::result_of<
					BinaryFunction (
						typename std::iterator_traits<LIterator>::reference,
						typename std::iterator_traits<RIterator>::reference
						)
				>::type
			>::type*,
			typename std::result_of<
				BinaryFunction (
					typename std::iterator_traits<LIterator>::reference,
					typename std::iterator_traits<RIterator>::reference
					)
			>::type
		>
	{
	public:
		typedef BinaryFunction functor_type;
		typedef LIterator iterator_type;
		typedef RIterator iterator2_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename std::result_of<
			BinaryFunction (
				typename std::iterator_traits<LIterator>::reference,
				typename std::iterator_traits<RIterator>::reference
				)
		>::type reference;
		typedef typename std::remove_reference<reference>::type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef value_type* pointer;
	protected:
		iterator_type current;
		iterator2_type current2;
		functor_type func;
	public:
		transform_iterator() = default;
		transform_iterator(transform_iterator const&) = default;
		SPROUT_CONSTEXPR transform_iterator(iterator_type it, iterator2_type it2)
			: current(it)
			, current2(it2)
		{}
		SPROUT_CONSTEXPR transform_iterator(iterator_type it, iterator2_type it2, functor_type func)
			: current(it)
			, current2(it2)
			, func(func)
		{}
		template<typename U, typename V, typename W>
		SPROUT_CONSTEXPR transform_iterator(transform_iterator<U, V, W> const& it)
			: current(it.current)
			, current2(it.current2)
			, func(it.func)
		{}
		template<typename U, typename V, typename W>
		transform_iterator& operator=(transform_iterator<U, V, W> const& it) {
			transform_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR iterator_type base2() const {
			return current2;
		}
		SPROUT_CONSTEXPR functor_type functor() const {
			return func;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return func(*current, *current2);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &func(*current, *current2);
		}
		transform_iterator& operator++() {
			++current;
			++current2;
			return *this;
		}
		transform_iterator operator++(int) {
			transform_iterator result(*this);
			++current;
			++current2;
			return result;
		}
		transform_iterator& operator--() {
			--current;
			--current2;
			return *this;
		}
		transform_iterator operator--(int) {
			transform_iterator temp(*this);
			--current;
			--current2;
			return temp;
		}
		SPROUT_CONSTEXPR transform_iterator operator+(difference_type n) const {
			return transform_iterator(current + n, current2 + n, func);
		}
		SPROUT_CONSTEXPR transform_iterator operator-(difference_type n) const {
			return transform_iterator(current - n, current2 - n, func);
		}
		transform_iterator& operator+=(difference_type n) {
			transform_iterator temp(current + n, current2 + n, func);
			temp.swap(*this);
			return *this;
		}
		transform_iterator& operator-=(difference_type n) {
			transform_iterator temp(current - n, current2 - n, func);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return func(current[n], current2[n]);
		}
		SPROUT_CONSTEXPR transform_iterator next() const {
			return transform_iterator(sprout::next(current), sprout::next(current2), func);
		}
		SPROUT_CONSTEXPR transform_iterator prev() const {
			return transform_iterator(sprout::prev(current), sprout::prev(current2), func);
		}
		void swap(transform_iterator& other) {
			using std::swap;
			swap(current, other.current);
			swap(current2, other.current2);
			swap(func, other.func);
		}
	};

	//
	// transform_iterator
	//
	template<typename UnaryFunction, typename Iterator>
	class transform_iterator<UnaryFunction, Iterator, void>
		: public std::iterator<
			typename std::iterator_traits<Iterator>::iterator_category,
			typename std::remove_reference<
				typename std::result_of<
					UnaryFunction (typename std::iterator_traits<Iterator>::reference)
				>::type
			>::type,
			typename std::iterator_traits<Iterator>::difference_type,
			typename std::remove_reference<
				typename std::result_of<
					UnaryFunction (typename std::iterator_traits<Iterator>::reference)
				>::type
			>::type*,
			typename std::result_of<
				UnaryFunction (typename std::iterator_traits<Iterator>::reference)
			>::type
		>
	{
	public:
		typedef UnaryFunction functor_type;
		typedef Iterator iterator_type;
		typedef typename std::iterator_traits<iterator_type>::iterator_category iterator_category;
		typedef typename std::result_of<
			UnaryFunction (typename std::iterator_traits<Iterator>::reference)
		>::type reference;
		typedef typename std::remove_reference<reference>::type value_type;
		typedef typename std::iterator_traits<iterator_type>::difference_type difference_type;
		typedef value_type* pointer;
	protected:
		iterator_type current;
		functor_type func;
	public:
		transform_iterator() = default;
		transform_iterator(transform_iterator const&) = default;
		explicit SPROUT_CONSTEXPR transform_iterator(iterator_type it)
			: current(it)
		{}
		SPROUT_CONSTEXPR transform_iterator(iterator_type it, functor_type func)
			: current(it)
			, func(func)
		{}
		template<typename U, typename V>
		SPROUT_CONSTEXPR transform_iterator(transform_iterator<U, V> const& it)
			: current(it.current)
			, func(it.func)
		{}
		template<typename U, typename V>
		transform_iterator& operator=(transform_iterator<U, V> const& it) {
			transform_iterator temp(it);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR iterator_type base() const {
			return current;
		}
		SPROUT_CONSTEXPR functor_type functor() const {
			return func;
		}
		SPROUT_CONSTEXPR reference operator*() const {
			return func(*current);
		}
		SPROUT_CONSTEXPR pointer operator->() const {
			return &func(*current);
		}
		transform_iterator& operator++() {
			++current;
			return *this;
		}
		transform_iterator operator++(int) {
			transform_iterator result(*this);
			++current;
			return result;
		}
		transform_iterator& operator--() {
			--current;
			return *this;
		}
		transform_iterator operator--(int) {
			transform_iterator temp(*this);
			--current;
			return temp;
		}
		SPROUT_CONSTEXPR transform_iterator operator+(difference_type n) const {
			return transform_iterator(current + n, func);
		}
		SPROUT_CONSTEXPR transform_iterator operator-(difference_type n) const {
			return transform_iterator(current - n, func);
		}
		transform_iterator& operator+=(difference_type n) {
			transform_iterator temp(current + n, func);
			temp.swap(*this);
			return *this;
		}
		transform_iterator& operator-=(difference_type n) {
			transform_iterator temp(current - n, func);
			temp.swap(*this);
			return *this;
		}
		SPROUT_CONSTEXPR reference operator[](difference_type n) const {
			return func(current[n]);
		}
		SPROUT_CONSTEXPR transform_iterator next() const {
			return transform_iterator(sprout::next(current), func);
		}
		SPROUT_CONSTEXPR transform_iterator prev() const {
			return transform_iterator(sprout::prev(current), func);
		}
		void swap(transform_iterator& other) {
			using std::swap;
			swap(current, other.current);
			swap(func, other.func);
		}
	};

	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator==(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() == rhs.base();
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator!=(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs == rhs);
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() < rhs.base();
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return rhs < lhs;
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator<=(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return !(rhs < lhs);
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR bool operator>=(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return !(lhs < rhs);
	}
	template<
		typename UnaryOrBinaryFunction1, typename LIterator1, typename RIterator1,
		typename UnaryOrBinaryFunction2, typename LIterator2, typename RIterator2
	>
	inline SPROUT_CONSTEXPR decltype(std::declval<LIterator1>() - std::declval<LIterator2>()) operator-(
		sprout::transform_iterator<UnaryOrBinaryFunction1, LIterator1, RIterator1> const& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction2, LIterator2, RIterator2> const& rhs
		)
	{
		return lhs.base() - rhs.base();
	}
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> operator+(
		typename sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator>::difference_type n,
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> const& it
		)
	{
		return it + n;
	}

	//
	// make_transform_iterator
	//
	template<typename BinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<BinaryFunction, LIterator, RIterator>
	make_transform_iterator(LIterator it1, RIterator it2, BinaryFunction func) {
		return sprout::transform_iterator<BinaryFunction, LIterator, RIterator>(it1, it2, func);
	}
	template<typename UnaryFunction, typename Iterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryFunction, Iterator>
	make_transform_iterator(Iterator it, UnaryFunction func) {
		return sprout::transform_iterator<UnaryFunction, Iterator>(it, func);
	}

	//
	// swap
	//
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	void swap(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator>& lhs,
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator>& rhs
		)
		SPROUT_NOEXCEPT_EXPR(SPROUT_NOEXCEPT_EXPR(lhs.swap(rhs)))
	{
		lhs.swap(rhs);
	}

	//
	// distance
	//
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> >::difference_type
	distance(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> first,
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> last
		)
	{
		return last - first;
	}

	//
	// iterator_next
	//
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> iterator_next(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> const& it
		)
	{
		return it.next();
	}
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> iterator_next(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> const& it,
		typename sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator>::difference_type n
		)
	{
		return it + n;
	}

	//
	// iterator_prev
	//
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> iterator_prev(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> const& it
		)
	{
		return it.prev();
	}
	template<typename UnaryOrBinaryFunction, typename LIterator, typename RIterator>
	inline SPROUT_CONSTEXPR sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> iterator_prev(
		sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator> const& it,
		typename sprout::transform_iterator<UnaryOrBinaryFunction, LIterator, RIterator>::difference_type n
		)
	{
		return it - n;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_TRANSFORM_ITERATOR_HPP
