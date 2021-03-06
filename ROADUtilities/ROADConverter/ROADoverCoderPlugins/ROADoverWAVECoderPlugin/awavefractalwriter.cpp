#include "awavefractalwriter.h"

AWaveFractalWriter::AWaveFractalWriter(QString aFilePath,
                                       __WAVEDESCR aWaveDesc,
                                       __WAVEFORMAT awaveformat,
                                       __WAVEDESCRDATA aWaveData,
                                       __FRACDESCR aFractalFormat)
    : _waveDesc(aWaveDesc),
      _waveformat(awaveformat),
      _waveData(aWaveData),
      _fractalFormat(aFractalFormat),
      _averLength(0)
{
    do
    {

        _QFile.setFileName(aFilePath);

        _isOpen = _QFile.open(QIODevice::WriteOnly);

        if(!_isOpen)
            break;


        _isOpen = _tempFractalMapFile.open();

        if(!_isOpen)
            break;

        _isOpen = _tempFractalDataFile.open();

        if(!_isOpen)
            break;


        _dataStream.setDevice(&_QFile);

        _dataStream.setByteOrder(QDataStream::LittleEndian);

        writeHead();


        _fractalMapStream.setDevice(&_tempFractalMapFile);

        _fractalMapStream.setByteOrder(QDataStream::LittleEndian);

        _fractalDataStream.setDevice(&_tempFractalDataFile);

        _fractalDataStream.setByteOrder(QDataStream::LittleEndian);

    }
    while(false);


}

AWaveFractalWriter::~AWaveFractalWriter()
{
    closeFiles();
}

void AWaveFractalWriter::flushAndCloseFile()
{
    writeHead();

    writeFractInfo();

    closeFiles();
}

void AWaveFractalWriter::writeROADdata(char* aData, unsigned int aLength, unsigned int aPrelisteningCRC, unsigned int aROADdataCRC)
{
    // Writing the start position of the super frame

    qint64 lpos = _tempFractalDataFile.pos();

    _fractalMapStream << lpos;


    _tempFractalDataFile.write(aData, aLength);

}

void AWaveFractalWriter::reject()
{
    closeFiles();

    _QFile.remove();
}

void AWaveFractalWriter::writeHead()
{
    _QFile.seek(0);

    _waveData.chunkHead.size = _averLength;

    _waveDesc.chunkHead.size = _averLength + 36;

    _dataStream.writeRawData(_waveDesc.chunkHead.id, sizeof(_waveDesc.chunkHead.id));

    _dataStream << _waveDesc.chunkHead.size;

    _dataStream.writeRawData(_waveDesc.wave, sizeof(_waveDesc.wave));

    _dataStream.writeRawData(_waveformat.chunkHead.id, sizeof(_waveformat.chunkHead.id));

    _dataStream << _waveformat.chunkHead.size;

    _dataStream << _waveformat.format;

    _dataStream << _waveformat.channels;

    _dataStream << _waveformat.sampleRate;

    _dataStream << _waveformat.byteRate;

    _dataStream << _waveformat.blockAlign;

    _dataStream << _waveformat.bitsPerSample;

    _dataStream.writeRawData(_waveData.chunkHead.id, sizeof(_waveData.chunkHead.id));

    _dataStream << _waveData.chunkHead.size;
}

void AWaveFractalWriter::closeFiles()
{
    _QFile.close();

    _tempFractalMapFile.close();

    _tempFractalDataFile.close();
}

void AWaveFractalWriter::writeFractInfo()
{

    _fractalMap._chunkHead.size = _tempFractalMapFile.size();

    _fractalIndeces._chunkHead.size = _tempFractalDataFile.size();



    _tempFractalMapFile.seek(0);

    _tempFractalDataFile.seek(0);

    _QFile.seek(_QFile.size()-1);



    _dataStream.writeRawData(_fractalFormat._chunkHead.id, sizeof(_fractalFormat._chunkHead.id));

    _dataStream << _fractalFormat._chunkHead.size;

    _dataStream << _fractalFormat._format._format;

    _dataStream << _fractalFormat._format._superFrameLength;

    _dataStream << _fractalFormat._format._frameRangeLength;

    _dataStream << _fractalFormat._format._domainShift;

    _dataStream << _fractalFormat._format._domainShiftScale;

    _dataStream << _fractalFormat._format._originalAmountOfChannels;

    _dataStream << _fractalFormat._format._averDiffMode;

    _dataStream << _fractalFormat._format._encriptionCode;




    _dataStream.writeRawData(_fractalMap._chunkHead.id, sizeof(_fractalMap._chunkHead.id));

    _dataStream << _fractalMap._chunkHead.size;

    const char * lptrDataTempFractalMapFile = (char *)(_tempFractalMapFile.map(0, _tempFractalMapFile.size(), QFileDevice::NoOptions));

    _QFile.write(lptrDataTempFractalMapFile, _tempFractalMapFile.size());




    _dataStream.writeRawData(_fractalIndeces._chunkHead.id, sizeof(_fractalIndeces._chunkHead.id));

    _dataStream << _fractalIndeces._chunkHead.size;




    const char * lptrDataTempFractalDataFile = (char *)(_tempFractalDataFile.map(0, _tempFractalDataFile.size(), QFileDevice::NoOptions));

    _QFile.write(lptrDataTempFractalDataFile, _tempFractalDataFile.size());
}
