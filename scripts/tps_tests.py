import click


@click.command()
@click.option('--number', '-n', default=20000)
@click.option('--path', '-p', default='/opt/vast/bin')
def test(number, path):
    