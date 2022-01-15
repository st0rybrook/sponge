#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

//template <typename... Targs>
//void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _capacity(capacity),_buf(""),_write_cnt(0),_read_cnt(0),_flag_input_ended(false) {} 

size_t ByteStream::write(const string &data) {
    size_t len = 0;
    if (_buf.length()+data.length()<=_capacity){
        len = data.length();
        _buf += data;
    }else{
        len=_capacity-_buf.length();
        _buf += data.substr(0,len);
    }
    _write_cnt+=len;
    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t l=len<=_buf.length()?len:_buf.length();
    return _buf.substr(0,l);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t l=len<=_buf.length()?len:_buf.length();
    _read_cnt+=l;
    _buf=_buf.substr(l,_buf.length()-l);
    }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::string str = peek_output(len) ;
    pop_output(len);
    return str;
}

void ByteStream::end_input() {
    _flag_input_ended=true;
}

bool ByteStream::input_ended() const { return _flag_input_ended; }

size_t ByteStream::buffer_size() const { return _buf.length(); }

bool ByteStream::buffer_empty() const { return _buf.length()==0; }

bool ByteStream::eof() const { return _flag_input_ended&&buffer_empty(); }

size_t ByteStream::bytes_written() const { return _write_cnt; }

size_t ByteStream::bytes_read() const { return _read_cnt; }

size_t ByteStream::remaining_capacity() const { return _capacity-_buf.length(); }
