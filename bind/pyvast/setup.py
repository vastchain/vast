from setuptools import setup, find_packages

setup(
    name="pyvast",
    version="0.3",
    author="everiToken",
    author_email="help@everitoken.io",
    description="Python bind library for everiToken",
    long_description=open("README.rst").read(),
    license="MIT",
    url="https://github.com/everitoken/vast/tree/master/bind/pyvast",
    packages=find_packages(),
    install_requires=['cffi'],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux",
        "Operating System :: MacOS :: MacOS X"
    ],
)
