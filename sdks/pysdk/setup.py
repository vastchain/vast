from setuptools import find_packages, setup

setup(
    name='pyvastsdk',
    version='0.3',
    author='everiToken',
    author_email='help@everitoken.io',
    description='Python SDK library for everiToken',
    long_description=open('README.rst').read(),
    license='MIT',
    url='https://github.com/everitoken/vast/tree/master/sdks/pysdk',
    packages=find_packages(),
    install_requires=['pyvast', 'requests'],
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: POSIX :: Linux',
        'Operating System :: MacOS :: MacOS X'
    ],
)
